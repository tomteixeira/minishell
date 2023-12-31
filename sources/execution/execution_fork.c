/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/22 15:15:45 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_directory(const char *path)
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

void	check_directory(const char *command, t_minishell **cur)
{
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == -1)
		{
			ft_error("bash: %s: No such file or directory\n", command);
			ft_free(cur, 0);
			exit(127);
		}
		else if (is_directory(command))
		{
			ft_error("bash: %s: Is a directory\n", command);
			ft_free(cur, 0);
			exit(126);
		}
	}
}

void	handle_pipe_redirection(t_command_parser *current,
								int *pipefd,
								int *prev_pipe_read_fd)
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

int	no_heredoc_in_prompt(t_minishell *cur)
{
	t_redirection		*redir;
	t_command_parser	*cmd_parser;

	redir = NULL;
	cmd_parser = NULL;
	if (!cur || !cur->f_c || !cur->f_c->command)
		return (1);
	cmd_parser = cur->f_c;
	while (cmd_parser)
	{
		redir = cmd_parser->command->in_r;
		while (redir)
		{
			if (redir->type == HEREDOC)
				return (0);
			redir = redir->next;
		}
		cmd_parser = cmd_parser->next;
	}
	return (1);
}

void	handle_redirections_and_pipes(t_minishell **cur,
			int *pipefd, int *prev_pipe)
{
	if (no_heredoc_in_prompt(*cur))
	{
		handle_pipe_redirection((*cur)->f_c, pipefd, prev_pipe);
		handle_redirection(cur);
	}
	else
	{
		handle_redirection(cur);
		if ((*cur)->f_c->command->pipe_after && !(*cur)->f_c->command->out_r)
			handle_pipe_redirection((*cur)->f_c, pipefd, prev_pipe);
	}
}

void	handle_child_process(t_minishell **cur,
							int *pipefd,
							char **env,
							int *prev_pipe)
{
	char	*f_p;

	f_p = NULL;
	handle_redirections_and_pipes(cur, pipefd, prev_pipe);
	if ((*cur)->f_c->command->cargs)
	{
		check_directory((*cur)->f_c->command->cargs[0], cur);
		f_p = find_command_in_path((*cur)
				->f_c->command->cargs[0], env);
	}
	if ((*cur)->f_c->command->cargs && f_p && access(f_p, X_OK) != -1
		&& ft_strcmp((*cur)->f_c->command->cargs[0], ""))
		execve(f_p, (*cur)->f_c->command->cargs, env);
	else if ((*cur)->f_c->command->cargs[0])
	{
		if (f_p != NULL)
			free(f_p);
		ft_error("bash: %s: command not found\n",
			(*cur)->f_c->command->cargs[0]);
		ft_free(cur, 2);
		exit(127);
	}
}

void	handle_parent_process(t_minishell **current,
							int *pipefd,
							int *prev_pipe_read_fd)
{
	if ((*current)->f_c->command->pipe_after)
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
