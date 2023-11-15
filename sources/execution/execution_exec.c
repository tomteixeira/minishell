/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/13 10:21:27 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	fork_and_execute(t_command_parser **current,
	int *pipefd, int *prev_pipe_read_fd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		handle_child_process(*current, pipefd, env, prev_pipe_read_fd);
	else if (pid > 0)
		handle_parent_process(*current, pipefd, prev_pipe_read_fd);
	else
		exit_with_error("fork");
	return (pid);
}
