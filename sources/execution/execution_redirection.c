/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/21 17:54:30 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_with_error(const char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

// Handle output redirections
static void	handle_out_r(t_minishell **m)
{
	int	fd;

	fd = -1;
	while ((*m)->f_c->command->out_r)
	{
		if (fd != -1)
			close(fd);
		if ((*m)->f_c->command->out_r->type == R_OUT)
			fd = open((*m)->f_c->command->out_r->file,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if ((*m)->f_c->command->out_r->type == A_R_OUT)
			fd = open((*m)->f_c->command->out_r->file,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			ft_error_exit("bash: %s: %s\n", (*m)->f_c->command->out_r->file, m);
		(*m)->f_c->command->out_r = (*m)->f_c->command->out_r->next;
	}
	if (fd != -1)
	{
		if (dup2(fd, 1) == -1)
			exit_with_error("dup2");
		close(fd);
	}
}

// Handle input redirections
static void	handle_in_r(t_minishell **c)
{
	int	fd;

	fd = -1;
	while ((*c)->f_c->command->in_r)
	{
		if (fd != -1)
			close(fd);
		if ((*c)->f_c->command->in_r->type == R_IN)
		{
			fd = open((*c)->f_c->command->in_r->file, O_RDONLY);
			if (fd == -1)
				ft_error_exit("bash: %s: %s\n",
					(*c)->f_c->command->in_r->file, c);
		}
		else if ((*c)->f_c->command->in_r->type == HEREDOC)
			handle_heredoc((*c)->f_c->command->in_r, &fd);
		if (fd != -1)
		{
			if (dup2(fd, 0) == -1)
				exit_with_error("dup2");
			close(fd);
		}
		(*c)->f_c->command->in_r = (*c)->f_c->command->in_r->next;
	}
}

// Utility function to handle redirections
void	handle_redirection(t_minishell **m)
{
	handle_out_r(m);
	handle_in_r(m);
}
