/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/13 16:29:44 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
// Set up the child's input and output based on the piping
static void	setup_child_io(t_command_parser *current, int *pipefd)
{
	if (pipefd[0] != -1)
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
	}
	if (current->command->pipe_after)
	{
		dup2(pipefd[1], 1);
		close(pipefd[1]);
	}
}

// Execute the command in the child process
static void	execute_child_command(t_command_parser *current, char **env)
{
	char	*full_path;

	full_path = find_command_in_path(current->command->command_args[0]);
	if (full_path && access(full_path, X_OK) != -1)
	{
		execve(full_path, current->command->command_args, env);
		perror("execve");
		free(full_path);
		exit(EXIT_FAILURE);
	}
	else
	{
		write_error_msg(current->command->command_args[0],
			": command not found");
		exit(EXIT_FAILURE);
	}
}*/

void handle_child_process(t_command_parser *current, int *pipefd, char **env, int *prev_pipe_read_fd)
{
	char *full_path;

	// Check if there's a previous command in the pipeline
	if (current->previous && current->previous->command->pipe_after && *prev_pipe_read_fd != -1)
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

// Handle Parent Process
void handle_parent_process(t_command_parser *current, int *num_children,
	int *pipefd, int *prev_pipe_read_fd)
{
	(*num_children)++;
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