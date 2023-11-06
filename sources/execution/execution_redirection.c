/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/06 14:28:51 by hebernar         ###   ########.fr       */
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

void	exit_custom(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	ft_error(format, args);
	va_end(args);
	exit(EXIT_FAILURE);
}

void	exit_with_error(const char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
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
		write(STDOUT_FILENO, "heredoc> ", 9);  // Display the heredoc prompt
		line = get_next_line(STDERR_FILENO); // don't forget to secure memory leak
		remove_null_char(line);
		if (strcmp(line, delimiter) == 0) // don't forget to change the function
		{
			free(line);
			break ;
		}
		if (write(pipefd[1], line, strlen(line)) == -1
			|| write(pipefd[1], "\n", 1) == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
		free(line);
	}
}

// Utility function to handle heredoc redirections
void	handle_heredoc(t_redirection *heredoc, int *read_end)
{
	int	pipefd[2];

	setup_heredoc_pipe(pipefd);
	heredoc_read_and_write(pipefd, heredoc->file);
	close(pipefd[1]);
	*read_end = pipefd[0];
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
		{
			ft_error("bash: %s: %s\n", redir->file, strerror(errno));
			exit(EXIT_FAILURE);
		}
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
			{
				ft_error("bash: %s: %s\n", redir->file, strerror(errno));
				exit(EXIT_FAILURE);
			}
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
