/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:24:28 by toteixei          #+#    #+#             */
/*   Updated: 2023/03/29 12:01:33 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void	ft_read(int fd, char *buffer, char **line)
{
	int		bytes;
	char	*temp;

	if (!line[fd] || !ft_strchr(line[fd], '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		while (bytes > 0)
		{
			buffer[bytes] = 0;
			if (!line[fd])
				line[fd] = ft_substr(buffer, 0, bytes);
			else
			{
				temp = line[fd];
				line[fd] = ft_strjoin(temp, buffer);
			}
			if (ft_strchr(buffer, '\n'))
				break ;
			bytes = read(fd, buffer, BUFFER_SIZE);
		}
	}
	free(buffer);
	buffer = 0;
}

static char	*get_line(char **line, int fd)
{
	int		j;
	int		i;
	char	*temp;
	char	*ret;

	if (!line[fd])
		return (NULL);
	if (!ft_strchr(line[fd], '\n'))
	{
		ret = ft_substr(line[fd], 0, ft_strlen(line[fd]));
		free(line[fd]);
		line[fd] = 0;
		return (ret);
	}
	i = ft_strlen(line[fd]);
	j = ft_strlen(ft_strchr(line[fd], '\n'));
	ret = ft_substr(line[fd], 0, i - j + 1);
	temp = line[fd];
	line[fd] = ft_substr(ft_strchr(temp, '\n'), 1, j - 1);
	free(temp);
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*line[FOPEN_MAX];

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (BUFFER_SIZE < 1 || fd == -1 || read(fd, buffer, 0) < 0)
	{
		free(buffer);
		return (NULL);
	}
	ft_read(fd, buffer, line);
	if (line[fd] && line[fd][0] == 0)
	{
		free(line[fd]);
		line[fd] = NULL;
	}
	return (get_line(line, fd));
}
