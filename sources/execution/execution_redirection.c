/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/09 10:59:04 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_with_error(const char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

// Handle output redirections
static void	handle_out_redirection(t_redirection *redir)
{
	int	fd;

	fd = -1;
	while (redir)
	{
		if (fd != -1)
			close(fd);
		if (redir->type == R_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == A_R_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			ft_error_exit("bash: %s: %s\n", redir->file);
		redir = redir->next;
	}
	if (fd != -1)
	{
		if (dup2(fd, 1) == -1)
			exit_with_error("dup2");
		close(fd);
	}
}

// Handle input redirections
static void	handle_in_redirection(t_redirection *redir)
{
	int	fd;

	fd = -1;
	while (redir)
	{
		if (fd != -1)
			close(fd);
		if (redir->type == R_IN)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd == -1)
				ft_error_exit("bash: %s: %s\n", redir->file);
		}
		else if (redir->type == HEREDOC)
			handle_heredoc(redir, &fd);
		if (fd != -1)
		{
			if (dup2(fd, 0) == -1)
				exit_with_error("dup2");
			close(fd);
		}
		redir = redir->next;
	}
}

// Utility function to handle redirections
void	handle_redirection(t_command *cmd)
{
	handle_out_redirection(cmd->out_redirection);
	handle_in_redirection(cmd->in_redirection);
}
