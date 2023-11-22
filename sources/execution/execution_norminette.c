/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_norminette.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/22 15:38:55 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_line_and_handle_signal(char **line)
{
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	handle_exec_signal();
}

void	create_file(t_redirection *out)
{
	int	fd;

	while (out)
	{
		if (out->type == R_OUT)
			fd = open(out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (out->type == A_R_OUT)
			fd = open(out->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			perror("open");
		else
			close(fd);
		out = out->next;
	}
}

void	handle_redirections_and_continue(t_command_parser **command,
										int *pipefd,
										int *p_pipe)
{
	heredoc_read_and_write_bis((*command)->command->in_r);
	create_file((*command)->command->out_r);
	if ((*command)->command->pipe_after)
	{
		if (pipefd[1] != -1)
			close(pipefd[1]);
		*p_pipe = pipefd[0];
	}
	else
	{
		if (pipefd[0] != -1)
			close(pipefd[0]);
		if (pipefd[1] != -1)
			close(pipefd[1]);
		*p_pipe = -1;
	}
	*command = (*command)->next;
}
