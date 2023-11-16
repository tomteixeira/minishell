/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:22:49 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/16 14:36:01 by tomteixeira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*home_path(char *home_env)
{
	char	*home_path;
	int		i;
	int		len;
	int		j;

	i = 0;
	j = 0;
	while (home_env[i] && home_env[i] != '=')
		i++;
	len = i;
	while (home_env[len])
		len++;
	len -= i;
	home_path = malloc((len + 1) * sizeof(char));
	if (!home_path)
		return (NULL);
	
	while (j < len)
		home_path[j++] = home_env[++i];
	home_path[len] = '\0';
	return (home_path);
}

int	cd_home(char **env)
{
	int		i;
	char	*home;

	i = -1;
	while(env[++i])
	{
		if (ft_strncmp(env[i], "HOME", 4) == 0)
		{
			home = home_path(env[i]);
			if (!home)
				return (EXIT_FAILURE);
			printf("%s\n", home);
			if (chdir(home) != 0)
			{
				printf("bash: cd: %s: No such file or directory\n", home);
				free(home);
				return (EXIT_FAILURE);
			}
			free(home);
			return (EXIT_SUCCESS);
		}
	}
	ft_putstr_fd("bash: cd: HOME not set\n", 2);
	return (EXIT_FAILURE);
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
