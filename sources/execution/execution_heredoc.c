/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/22 15:43:16 by toteixei         ###   ########.fr       */
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

void	pid_to_str(char *str, pid_t pid)
{
	char	*ptr;
	char	*start;
	char	temp;
	char	*end;

	if (pid == 0)
	{
		*str = '0';
		*(str + 1) = '\0';
		return ;
	}
	ptr = str;
	while (pid > 0)
	{
		*ptr++ = '0' + (pid % 10);
		pid /= 10;
	}
	*ptr = '\0';
	start = str;
	end = ptr - 1;
	while (end > start)
	{
		temp = *start;
		*start++ = *end;
		*end-- = temp;
	}
}

int	handle_heredoc(t_redirection *heredoc, int *read_end)
{
	int		tempf;
	char	temp_file[64] = "/tmp/minishell_heredoc_";
	char	pid_str[20];
	char	*buff;

	pid_to_str(pid_str, getpid());
	strcat(temp_file, pid_str);
	tempf = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tempf < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		buff = readline("heredoc> ");
		if (!buff)
		{
			ft_putchar_fd('\n', 2);
			break ;
		}
		if (!strcmp(buff, heredoc->file))
		{
			free(buff);
			break ;
		}
		write(tempf, buff, strlen(buff));
		write(tempf, "\n", 1);
		free(buff);
	}
	close(tempf);
	*read_end = open(temp_file, O_RDONLY);
	unlink(temp_file);
	if (*read_end < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (0);
}
