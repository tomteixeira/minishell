/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:20:56 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/16 14:28:03 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*custom_prompt(void)
{
	char	cwd[PATH_MAX];
	char	*cwd_color;
	char	*reset_color;

	cwd_color = "\033[36m";
	reset_color = "\033[0m";
	getcwd(cwd, PATH_MAX);
	printf("\033[0;33m\033[0m%s%s%s", cwd_color, cwd, reset_color);
	if (g_signal != 0)
		printf("\033[31m - %d", g_signal);
	printf("\e[32m\e[1m ❯ \e[0m");
	return (readline(""));
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
