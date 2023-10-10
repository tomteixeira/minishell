/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/08 13:24:53 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Utility function to write an error message to stderr
void write_error_msg(const char *msg1, const char *msg2)
{
	write(2, msg1, ft_strlen(msg1));
	if (msg2)
		write(2, msg2, ft_strlen(msg2));
	write(STDERR_FILENO, "\n", 1);
}

// Initialize Execution Context
static void init_execution_context(t_command_parser **current, int *num_children, int *prev_pipe_read_fd, t_command_parser *first_command)
{
	*num_children = 0;
	*current = first_command;
	*prev_pipe_read_fd = -1;
}

// Handle Piping
static void handle_piping(t_command *cmd, int *pipefd)
{
	if (cmd->pipe_after)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

// Handle Child Process
static void handle_child_process(t_command_parser *current, int *pipefd, char **env)
{
	char *full_path;
	if (pipefd[0] != -1)
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
	}
	if (current->command->pipe_after)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
	}
	handle_redirection(current->command);
	full_path = find_command_in_path(current->command->command_args[0]);
	if (full_path && access(full_path, X_OK) != -1)
	{
		execve(full_path, current->command->command_args, env);
		free(full_path);
	}
	else
	{
		write_error_msg(current->command->command_args[0], ": command not found");
		exit(EXIT_FAILURE);
	}
}

// 4. Handle Parent Process
static void handle_parent_process(t_command_parser *current, int *num_children, int *pipefd, int *prev_pipe_read_fd)
{
	(*num_children)++;
	if (*prev_pipe_read_fd != -1)
		close(*prev_pipe_read_fd);
	if (current->command->pipe_after)
	{
		close(pipefd[1]);
		*prev_pipe_read_fd = pipefd[0];
	}
	else
		wait(NULL);
}

// 5. Wait for Children
static void wait_for_children(int num_children)
{
	while (num_children > 0)
	{
		wait(NULL);
		num_children--;
	}
}

// Utility function to execute a command
void execute_command(t_command_parser *first_command, char **env)
{
	t_command_parser *current;
	pid_t pid;
	int pipefd[2] = {-1, -1};
	int num_children;
	int prev_pipe_read_fd;

	init_execution_context(&current, &num_children, &prev_pipe_read_fd, first_command);
	while (current)
	{
		handle_piping(current->command, pipefd);
		pid = fork();
		if (pid == 0)
		{
			handle_child_process(current, pipefd, env);
		}
		else if (pid > 0)
			handle_parent_process(current, &num_children, pipefd, &prev_pipe_read_fd);
		else
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		current = current->next;
	}
	wait_for_children(num_children);
}
