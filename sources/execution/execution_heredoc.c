/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/21 18:17:41 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
// Utility function to remove /n from char* with creating memory leak
void	remove_null_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
}*/

// Utility function to setup the heredoc pipe
void	setup_heredoc_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(errno);
	}
}

void	heredoc_read_and_write_bis(t_redirection *redir)
{
	char	*line;

	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			handle_input_signal();
			while (1)
			{
				line = readline("heredoc> ");
				if (line == NULL)
				{
					ft_putchar_fd('\n', 2);
					return (handle_exec_signal());
				}
				if (ft_strcmp(line, (char *) redir->file) == 0)
				{
					free_line_and_handle_signal(&line);
					break ;
				}
				free(line);
			}
		}
		redir = redir->next;
	}
}
/*
// Utility function to read and write lines for heredoc
void	heredoc_read_and_write(int pipefd[2], const char *delimiter)
{
	char	*line;

	while (1)
	{
		write(STDERR_FILENO, "heredoc> ", 9);
		line = readline(NULL);
		if (line == NULL)
		{
			printf("\n");
			return ;
		}
		if (strcmp(line, delimiter) == 0)
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
*/

// Utility function to concatenate strings with a newline
char *concat_with_newline(char *original, char *addition) {
	char *new_str;
	size_t len_original = original ? strlen(original) : 0;
	size_t len_addition = addition ? strlen(addition) : 0;

	new_str = malloc(len_original + len_addition + 2); // +2 for newline and null terminator
	if (!new_str) return NULL;
	if (original) strcpy(new_str, original);
	if (addition) strcpy(new_str + len_original, addition);
	new_str[len_original + len_addition] = '\n';
	new_str[len_original + len_addition + 1] = '\0';

	free(original);
	return new_str;
}

// Modified function to handle heredoc input collection
void heredoc_read_and_write(int pipefd[2], t_redirection *heredoc) {
	char *line, *collected_input = NULL;

	while (heredoc) {
		if (heredoc->type == HEREDOC) {
			while (1) {
				line = readline("heredoc> ");
				if (!line || strcmp(line, heredoc->file) == 0) {
					free(line);
					break;
				}
				collected_input = concat_with_newline(collected_input, line);
				free(line);
			}
		}
		heredoc = heredoc->next;
	}

	// Write all collected input to the pipe
	if (collected_input) {
		if (write(pipefd[1], collected_input, strlen(collected_input)) == -1) {
			perror("write");
			exit(EXIT_FAILURE);
		}
		free(collected_input);
	}
}

// Function to handle heredoc redirections
int handle_heredoc(t_redirection *heredoc, int *read_end) {
	int pipefd[2];

	g_signal = 0;
	setup_heredoc_pipe(pipefd);
	heredoc_read_and_write(pipefd, heredoc);
	close(pipefd[1]);
	*read_end = pipefd[0];
	return 0;
}
