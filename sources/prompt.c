/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:20:56 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/20 15:30:10 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*custom_prompt(void)
{
	char	cwd[PATH_MAX];
	char	*prompt;
	char	*line;
	char	*buffer;

	getcwd(cwd, PATH_MAX);
	prompt = ft_strjoin("\033[36m", cwd);
	buffer = ft_strdup(prompt);
	free(prompt);
	prompt = ft_strjoin(buffer, "\033[0m\e[32m\e[1m ❯ \e[0m");
	line = readline(prompt);
	free(prompt);
	free(buffer);
	return (line);
}

char	*read_line(void)
{
	char	*line;

	line = custom_prompt();
	if (!line)
		return (NULL);
	add_history(line);
	return (line);
}
