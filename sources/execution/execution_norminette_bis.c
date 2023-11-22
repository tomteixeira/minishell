/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_norminette_bis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/22 15:30:32 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_stdin_to_fd(int fd)
{
	if (fd != -1)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			exit_with_error("dup2");
		close(fd);
	}
}

int	create_temp_file(const char *temp_file_path)
{
	int	tempf;

	tempf = open(temp_file_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tempf < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return tempf;
}


void write_to_temp_file(int tempf, const char *delimiter)
{
	char	*buff;
	while (1)
	{
		buff = readline("heredoc> ");
		if (!buff)
		{
			ft_putchar_fd('\n', 2);
			break;
		}
		if (!strcmp(buff, delimiter))
		{
			free(buff);
			break;
		}
		write(tempf, buff, strlen(buff));
		write(tempf, "\n", 1);
		free(buff);
	}
}
