/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:22:49 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/15 19:25:34 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_home(char **env)
{
	int		i;

	i = -1;
	while(env[++i])
	{
		if (ft_strcmp(env[i], "HOME") == 0)
	}
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return (EXIT_FAILURE);
	}
	if (chdir(home) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", home);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	cd(char **args, char **env)
{
	if (!args[1])
		return (cd_home(env));
	if (chdir(args[1]) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", args[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
