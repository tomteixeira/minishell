/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:22:53 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/15 13:08:20 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *set_var(char *arg)
{
    int i;
    int equal;

    i = 0;
    equal = 0;
    if (arg[i] == '=')
    {
        printf("bash: export: `%s': not a valid identifier\n", arg);
        return (NULL);
    }
    while (arg[i])
    {
        if (equal == 0 && !ft_isalpha(arg[i]) && arg[i] != '_')
        {
            printf("bash: export: `%s': not a valid identifier\n", arg);
            return (NULL);
        }
        if (arg[i] == '=')
            equal = 1;
        i++;
    }
    return (NULL);
}

char    **set_new_env(char *var, char **env)
{
    char    **new_env;
    int     i;
    int     env_count;
    
    new_env = NULL;
    env_count = 0;
    while (env[env_count])
        env_count++;
    new_env = malloc((env_count + 1) * sizeof(char *));
    if (!new_env)
        return (EXIT_FAILURE);
    i = -1;
    while (++i < env_count)
    {
        new_env[i] = ft_strdup(env[i]);
        if (!new_env[i])
            return (ft_free_arrays_i(new_env, i), EXIT_FAILURE);
    }
    new_env[env_count] = NULL;

    return (new_env);
}

int     export(char **args, char **env)
{
    int     i;
    char    *var;
    char    **env_buffer;
    
    if (!args[1])
    {
        ft_putstr_fd("bash: export: missing arguments\n", 2);
        return (EXIT_FAILURE);
    }
    i = 1;
    while (args[i])
    {
        var = NULL;
        var = set_var(args[i]);
        if (var)
        {
            env_buffer = env;
            env = set_new_env(var, env_buffer);
            free(env_buffer);
        }
        i++;
    }
    
    return (EXIT_SUCCESS);
}