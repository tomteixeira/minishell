/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:23:21 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/18 16:53:24 by tomteixeira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_var(char *var, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_strlen(var)) == 0)
		{
			printf("key find\n");
			return (1);
		}
		i++;
	}
	return (0);
}

char	**unset_var(char *var, char **env)
{
	char	**new_env;
	int		i;
	int		j;
	int		env_count;

	new_env = NULL;
    env_count = 0;
    while (env[env_count])
        env_count++;
    new_env = malloc((env_count - 1) * sizeof(char *));
    if (!new_env)
        return (NULL);
    i = 0;
	j = 0;
	while (i < env_count - 1)
    {
		if (ft_strncmp(var, env[i], ft_strlen(var)) != 0)
        {
			new_env[i++] = ft_strdup(env[j++]);
        	if (!new_env[i])
            	return (ft_free_arrays_i(new_env, i), NULL);
		}
		else
			j++;
    }
    new_env[i] = NULL;
    return (new_env);
}

int unset(char **args, char ***env)
{
    int     i;
    char    **env_buffer;

    i = 1;
    if (!args[i])
        return (EXIT_SUCCESS);
    while (args[i])
    {
        if (check_var(args[i], *env) == 1)
		{
			env_buffer = *env;
        	*env = unset_var(args[i], env_buffer);
        	if (!*env)
           		return (EXIT_FAILURE);
        	ft_free_arrays_i(env_buffer, -1);
		}
    }
	return (EXIT_SUCCESS);
}