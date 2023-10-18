/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/18 12:58:43 by tomteixeira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_signal = 0;

// Check Assignment

int is_assignment(const char *cmd)
{
	if (strchr(cmd, '='))
		return (1);
	return (0);
}

// Handle Piping
static void	handle_piping(t_command *cmd, int *pipefd)
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

// Function to reset signal handlers to default behaviors for child processes
static void	reset_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGSEGV, SIG_DFL);
}

// Function to handle the fork and execute logic
static void fork_and_execute(t_command_parser **current, int *num_children,
	int *pipefd, int *prev_pipe_read_fd, char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		reset_child_signals();
		handle_child_process(*current, pipefd, env, prev_pipe_read_fd);
	}
	else if (pid > 0)
	{
		if (*prev_pipe_read_fd != -1)
			close(*prev_pipe_read_fd);
		handle_parent_process(*current, num_children,
			pipefd, prev_pipe_read_fd);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

// Function to wait for all child processes to complete
static int wait_for_children(int num_children)
{
	int status;
	pid_t child_pid;

	while (num_children > 0)
	{
		child_pid = waitpid(-1, &status, 0);
		if (child_pid == -1)
		{
			perror("waitpid error");
			exit(EXIT_FAILURE);
		}
		if (WIFSIGNALED(status))
		{
			put_sig(WTERMSIG(status));
			g_signal = 128 + WTERMSIG(status);
			return (g_signal);
		}
		else if (WIFEXITED(status))
			g_signal = WEXITSTATUS(status);
		num_children--;
	}
	return (g_signal);
}


// Utility function to execute a command
int execute_command(t_command_parser *first_command, char **env)
{
	t_command_parser *current;
	int pipefd[2];
	int num_children;
	int prev_pipe_read_fd;

	num_children = 0;
	pipefd[0] = -1;
	pipefd[1] = -1;
	init_execution_context(&current, &num_children, &prev_pipe_read_fd, first_command);
	while (current)
	{
		expand_command_arguments(current->command, env);
//		if (is_assignment(current->command->command_args[0]) && current->command->command_args[1] == NULL)
//		{
//			char *assignment_args[3];
//			assignment_args[0] = "export";
//			assignment_args[1] = current->command->command_args[0];
//			assignment_args[2] = NULL;
//			export(assignment_args, env);
//			current = current->next;
//			continue;
//		}
		if (execute_builtin(current->command, env))
		{
			current = current->next;
			continue;
		}
		expand_command_arguments(current->command, env);
		handle_piping(current->command, pipefd);
		fork_and_execute(&current, &num_children, pipefd, &prev_pipe_read_fd, env);
		current = current->next;
	}
	return wait_for_children(num_children);
}


/*
int execute_command(t_command_parser *first_command, char **env)
{
	t_command_parser *current;
	char *full_path;
	pid_t pid;
	int status;
	int num_children = 0;

	int pipefd[2];  // for the current pipe
	int prev_pipe_read_fd = -1;  // to store the read end of the previous pipe

	current = first_command;
	while (current)
	{
		if (current->command->pipe_after)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}

		pid = fork();
		if (pid == 0)  // child process
		{
			if (prev_pipe_read_fd != -1)
			{
				dup2(prev_pipe_read_fd, 0);  // Set stdin to previous pipe's read end
				close(prev_pipe_read_fd);
			}
			if (current->command->pipe_after)
			{
				close(pipefd[0]);  // Close read end, since we are going to write
				dup2(pipefd[1], 1);  // Redirect stdout to the write end of the pipe
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
				write_error_msg("Command not found: ", current->command->command_args[0]);
				exit(EXIT_FAILURE);
			}
		}
		else if (pid > 0)  // parent process
		{
			num_children++;
			if (prev_pipe_read_fd != -1)
				close(prev_pipe_read_fd);

			if (current->command->pipe_after)
			{
				close(pipefd[1]);
				prev_pipe_read_fd = pipefd[0];
			}
			else
			{
				wait(&status);  // Wait only if it's the last command
			}
		}
		else
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		current = current->next;
	}
	while (num_children > 0)
	{
		wait(NULL);
		num_children--;
	}
	return(0);
//	return (wait_for_children(num_children));
}*/