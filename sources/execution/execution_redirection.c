/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/10 14:06:32 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Utility function to setup the heredoc pipe
static void setup_heredoc_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

// Utility function to read and write lines for heredoc
static void heredoc_read_and_write(int pipefd[2], const char *delimiter) {
	char *line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			write_error_msg("Unexpected EOF while looking for heredoc delimiter", NULL);
			exit(EXIT_FAILURE);
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		if (write(pipefd[1], line, strlen(line)) == -1 ||
		    write(pipefd[1], "\n", 1) == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
		free(line);
	}
}

// Utility function to handle heredoc redirections
static void handle_heredoc(t_redirection *heredoc, int *read_end) {
	int pipefd[2];

	setup_heredoc_pipe(pipefd);
	heredoc_read_and_write(pipefd, heredoc->file);
	close(pipefd[1]);
	*read_end = pipefd[0];
}

// Handle output redirections
static void handle_out_redirection(t_redirection *redir) {
	int fd = -1;
	while (redir)
	{
		if (fd != -1)
			close(fd);
		if (redir->type == R_OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		} else if (redir->type == A_R_OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		redir = redir->next;
	}

	if (fd != -1)
	{
		if (dup2(fd, 1) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
}

// Handle input redirections
static void handle_in_redirection(t_redirection *redir) {
    int fd = -1;
    while (redir) {
        if (fd != -1)
            close(fd);

        if (redir->type == R_IN) {
            fd = open(redir->file, O_RDONLY);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
        } else if (redir->type == HEREDOC) {
            handle_heredoc(redir, &fd);
        }

        if (fd != -1) {
            if (dup2(fd, 0) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(fd);
        }

        redir = redir->next;
    }
}

// Utility function to handle redirections
void handle_redirection(t_command *cmd)
{
    handle_out_redirection(cmd->out_redirection);
    handle_in_redirection(cmd->in_redirection);
}