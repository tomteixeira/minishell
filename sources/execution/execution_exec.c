/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/09 14:46:27 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setup_child_process(t_command_parser **current,
	int *pipefd, int *prev_pipe_read_fd, char **env)
{
	if (*prev_pipe_read_fd != -1)
	{
		dup2(*prev_pipe_read_fd, STDIN_FILENO);
		close(*prev_pipe_read_fd);
	}
	if ((*current)->command->pipe_after)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	handle_child_process(*current, pipefd, env, prev_pipe_read_fd);
	exit(EXIT_FAILURE);
}

static void	setup_parent_process(t_command_parser **current,
	int *pipefd, int *prev_pipe_read_fd)
{
	if ((*current)->command->pipe_after)
	{
		close(pipefd[1]);
		*prev_pipe_read_fd = pipefd[0];
	}
	else
		*prev_pipe_read_fd = -1;
	handle_parent_process(*current, pipefd, prev_pipe_read_fd);
}

pid_t	fork_and_execute(t_command_parser **current,
	int *pipefd, int *prev_pipe_read_fd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		setup_child_process(current, pipefd, prev_pipe_read_fd, env);
	else if (pid > 0)
		setup_parent_process(current, pipefd, prev_pipe_read_fd);
	else
		exit_with_error("fork");
	return (pid);
}
