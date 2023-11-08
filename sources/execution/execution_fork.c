/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/08 18:15:24 by tomteixeira      ###   ########.fr       */
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
	if (strchr(command, '/'))
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
	}
	if (current->command->pipe_after)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
	}
}

void	handle_child_process(t_command_parser *current,
	int *pipefd, char **env, int *prev_pipe_read_fd)
{
	char	*full_path;

	handle_pipe_redirection(current, pipefd, prev_pipe_read_fd);
	handle_redirection(current->command);
	if (current->command->command_args)
	{
		check_directory(current->command->command_args[0]);
		full_path = find_command_in_path(current->command->command_args[0]);
	}
	if (current->command->command_args && full_path && access(full_path, X_OK) != -1 && ft_strcmp(current->command->command_args[0],""))
	{
		execve(full_path, current->command->command_args, env);
		free(full_path);
	}
	else if (current->command->command_args[0])
	{
		ft_error("bash: %s: command not found\n",
			current->command->command_args[0]);
		free(full_path);
		exit(127);
	}
}

// Handle Parent Process
void	handle_parent_process(t_command_parser *current, int *pipefd, int *prev_pipe_read_fd)
{
	if (!current->command->pipe_after && *prev_pipe_read_fd != -1)
		close(*prev_pipe_read_fd);
	if (current->command->pipe_after)
	{
		close(pipefd[1]);
		*prev_pipe_read_fd = pipefd[0];
	}
	else
	{
		if (pipefd[0] != -1)
			close(pipefd[0]);
		if (pipefd[1] != -1)
			close(pipefd[1]);
	}
}