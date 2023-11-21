/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/21 15:26:04 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Duplication of standard file descriptors
static void	duplicate_std_fds(int *original_stdout, int *original_stdin)
{
	*original_stdout = dup(STDOUT_FILENO);
	*original_stdin = dup(STDIN_FILENO);
	if (*original_stdout == -1 || *original_stdin == -1)
		exit_with_error("dup");
}

// Executing the built-in command
static void	execute_builtin_wrapper(t_minishell **current, char ***env)
{
	handle_redirection((*current)->f_c->command);
	execute_builtin(current, env);
}

// Restoring the original standard file descriptors
static void	restore_std_fds(int original_stdout, int original_stdin)
{
	dup2(original_stdout, STDOUT_FILENO);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdout);
	close(original_stdin);
}

// The refactored execute_builtin_command function
int	execute_builtin_command(t_minishell **current,
	char ***env, int *prev_pipe, int pipefd[2])
{
	int		original_stdout;
	int		original_stdin;

	duplicate_std_fds(&original_stdout, &original_stdin);
	if (*prev_pipe != -1)
	{
		dup2(*prev_pipe, STDIN_FILENO);
		close(*prev_pipe);
	}
	if ((*current)->f_c->command->pipe_after)
		dup2(pipefd[1], STDOUT_FILENO);
	execute_builtin_wrapper(current, env);
	restore_std_fds(original_stdout, original_stdin);
	if ((*current)->f_c->command->pipe_after)
	{
		*prev_pipe = pipefd[0];
		close(pipefd[1]);
	}
	else
		*prev_pipe = -1;
	(*current)->f_c = (*current)->f_c->next;
	return (1);
}
