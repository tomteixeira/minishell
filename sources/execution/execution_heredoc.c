/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/22 15:30:42 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
}

// Utility function to setup the heredoc pipe and check that the pipe is empty
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
				if (ft_strcmp(line, (char *)redir->file) == 0)
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

void	open_temp_file_for_reading(const char *temp_file_path, int *read_end)
{
	*read_end = open(temp_file_path, O_RDONLY);
	if (*read_end < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	unlink(temp_file_path);
}

int	handle_heredoc(t_redirection *heredoc, int *read_end)
{
	char	*temp_file;
	int		tempf;

	temp_file = ft_strdup("/tmp/heredoc");
	tempf = create_temp_file(temp_file);
	write_to_temp_file(tempf, heredoc->file);
	close(tempf);
	open_temp_file_for_reading(temp_file, read_end);
	free(temp_file);
	return (0);
}
