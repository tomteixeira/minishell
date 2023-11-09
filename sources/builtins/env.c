/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:22:57 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/09 17:06:48 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_putstr(char *str)
{
	ft_putstr_fd(str, STDOUT_FILENO);
}

int	ft_env(char **args, char **envp)
{
	(void)args;
	while (*envp)
	{
		ft_putstr(*envp);
		write(STDOUT_FILENO, "\n", 1);
		envp++;
	}
	return (EXIT_SUCCESS);
}
