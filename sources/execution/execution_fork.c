/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/15 15:06:44 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_directory(const char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

static void	check_directory(const char *command)
{
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == -1)
		{
			ft_error("bash: %s: No such file or directory\n", command);
			exit(127);
		}
		else if (is_directory(command))
		{
			ft_error("bash: %s: Is a directory\n", command);
			exit(126);
		}
	}
}

void	handle_pipe_redirection(t_command_parser *current,
	int *pipefd, int *prev_pipe_read_fd)
{
	if (current->previous && current->previous->command->pipe_after
		&& *prev_pipe_read_fd != -1)
	{
		dup2(*prev_pipe_read_fd, 0);
		close(*prev_pipe_read_fd);
		if (pipefd[0] != -1)
			close(pipefd[0]);
	}
	if (current->command->pipe_after && pipefd[1] != -1)
	{
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		if (pipefd[0] != -1)
			close(pipefd[0]);
	}
}

void	handle_child_process(t_command_parser *current,
	int *pipefd, char **env, int *prev_pipe)
{
	char	*f_p;

	handle_pipe_redirection(current, pipefd, prev_pipe);
	handle_redirection(current->command);
	if (current->command->command_args)
	{
		check_directory(current->command->command_args[0]);
		f_p = find_command_in_path(current->command->command_args[0], env);
	}
	if (current->command->command_args && f_p
		&& access(f_p, X_OK) != -1
		&& ft_strcmp(current->command->command_args[0], ""))
	{
		execve(f_p, current->command->command_args, env);
		free(f_p);
	}
	else if (current->command->command_args[0])
	{
		ft_error("bash: %s: command not found\n",
			current->command->command_args[0]);
		free(f_p);
		exit(127);
	}
}

void	handle_parent_process(t_command_parser *current,
	int *pipefd, int *prev_pipe_read_fd)
{
	if (current->command->pipe_after)
	{
		if (pipefd[1] != -1)
			close(pipefd[1]);
		*prev_pipe_read_fd = pipefd[0];
	}
	else
	{
		if (pipefd[0] != -1)
			close(pipefd[0]);
		if (pipefd[1] != -1)
			close(pipefd[1]);
		*prev_pipe_read_fd = -1;
	}
}
