/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/15 15:33:41 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Check if the last command piped is a builtin
int	set_flag(t_command_parser **first_command)
{
	t_command_parser	*current;
	int					flag_last;

	current = *first_command;
	flag_last = 0;
	while (current)
	{
		if (current->command->pipe_after == 0
			&& is_builtin(current->command->command_args[0]))
			flag_last = 1;
		current = current->next;
	}
	return (flag_last);
}

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
	*current = (*current)->next;
	return (pid);
}
