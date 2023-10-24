/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/24 02:25:13 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_signal = 0;

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

// Function to handle the fork and execute logic
static pid_t	fork_and_execute(t_command_parser **current, pid_t pid,
	int *pipefd, int *prev_pipe_read_fd, char **env)
{
	//pid_t	pid;
	pid = fork();
	if (pid == 0)
	{
		if (!(*current)->command->pipe_after && pipefd[1] != -1)
			close(pipefd[1]);
		handle_child_process(*current, pipefd, env, prev_pipe_read_fd);
	}
	else if (pid > 0)
	{
		if ((*current)->command->pipe_after && pipefd[1] != -1)
			close(pipefd[1]);
		if (*prev_pipe_read_fd != -1)
			close(*prev_pipe_read_fd);
		handle_parent_process(*current, pipefd, prev_pipe_read_fd);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

// Function to wait for all child processes to complete
static int	wait_for_children(pid_t pid)
{
	int		status;

	while (waitpid(pid, &status, 0) != -1)
		;
	if (WIFSIGNALED(status))
	{
		put_sig(WTERMSIG(status));
		g_signal = 128 + WTERMSIG(status);
		return (g_signal);
	}
	else if (WIFEXITED(status))
		g_signal = WEXITSTATUS(status);
	return (g_signal);
}

// Utility function to handle assignments $> a=b
int	handle_assignments(t_command_parser **current, char ***env)
{
	char	*assignment_args[3];

	if (!(*current)->command->command_args)
		return (0);
	if (is_assignment((*current)->command->command_args[0])
		&& (*current)->command->command_args[1]
		== NULL && (*current)->next == NULL)
	{
		assignment_args[0] = "export";
		assignment_args[1] = (*current)->command->command_args[0];
		assignment_args[2] = NULL;
		export(assignment_args, env);
		*current = (*current)->next;
		return (1);
	}
	else if (is_assignment((*current)->command->command_args[0]))
		(*current)->command->command_args
			= remove_from_list((*current)->command->command_args,
				(*current)->command->command_args[0]);
	return (0);
}

// Utility function to execute a command
int	execute_command(t_command_parser *first_command, char ***env)
{
	t_command_parser	*current;
	int					pipefd[2];
	int					prev_pipe;
	pid_t				pid;

	pipefd[0] = -1;
	pipefd[1] = -1;
	pid = 0;
	init_execution_context(&current, &prev_pipe, first_command);
	while (current)
	{
		if (handle_assignments(&current, env))
			continue ;
		expand_command_arguments(current->command, *env);
		handle_piping(current->command, pipefd);
		if (execute_builtin(current->command, env))
		{
			current = current->next;
			continue ;
		}
		if (!current->command->command_args && current->command->in_redirection->type == HEREDOC)
		{
			handle_heredoc(current->command->in_redirection, &prev_pipe);
			g_signal = 0;
			return(0);
		}
		else
			pid = fork_and_execute(&current, pid, pipefd, &prev_pipe, *env);
		current = current->next;
	}
	return (wait_for_children(pid));
}
