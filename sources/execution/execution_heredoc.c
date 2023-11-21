/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/20 23:41:03 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Utility function to remove /0 from char*
static void	remove_null_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
}

// Utility function to setup the heredoc pipe
static void	setup_heredoc_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(errno);
	}
}

// Utility function to read and write lines for heredoc
static void	heredoc_read_and_write(int pipefd[2], const char *delimiter)
{
	char	*line;

	while (1)
	{
		write(STDERR_FILENO, "heredoc> ", 9);
		line = get_next_line(STDERR_FILENO);
		remove_null_char(line);
		if (ft_strcmp(line, (char *) delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (write(pipefd[1], line, ft_strlen(line)) == -1
			|| write(pipefd[1], "\n", 1) == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
		free(line);
	}
}

// Utility function to handle heredoc redirections
int	handle_heredoc(t_redirection *heredoc, int *read_end)
{
	int	pipefd[2];

	g_signal = 0;
	setup_heredoc_pipe(pipefd);
	heredoc_read_and_write(pipefd, heredoc->file);
	close(pipefd[1]);
	*read_end = pipefd[0];
	return (0);
}
