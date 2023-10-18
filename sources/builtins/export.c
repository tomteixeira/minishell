/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:22:53 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/18 12:51:25 by tomteixeira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    export_no_args(char **env)
{
    int i;
    int j;

    i = -1;
    while (env[++i])
    {
        write(1, "declare -x ", 11);
        j = -1;
        while (env[i][++j])
        {
            if (env[i][j] == '=')
            {
                write(1, &env[i][j], 1);
                write(1, "\"", 1);
                while (env[i][++j])
                    write(1, &env[i][j], 1);
                write(1, "\"", 1);
                break ;
            }
            write(1, &env[i][j], 1);
        }
        write(1, "\n", 1);
    }
}

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
        if (arg[i] == '=')
            equal = 1;
        if (equal == 0 && (!ft_isalpha(arg[i]) && arg[i] != '_'))
        {
            printf("bash: export: `%s': not a valid identifier\n", arg);
            return (NULL);
        }
        i++;
    }
    return (arg);
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
        return (NULL);
    i = -1;
    while (++i < env_count)
    {
        new_env[i] = ft_strdup(env[i]);
        if (!new_env[i])
            return (ft_free_arrays_i(new_env, i), NULL);
    }
    new_env[env_count] = var;
    new_env[env_count + 1] = NULL;

    return (new_env);
}

int     export(char **args, char **env)
{
    int     i;
    char    *var;
    //char    **env_buffer;
    
    if (!args[1])
    {
        export_no_args(env);
        return (EXIT_SUCCESS);
    }
    i = 1;
    while (args[i])
    {
        var = NULL;
        var = set_var(args[i]);
        if (var)
        {
            //env_buffer = env;
            env = set_new_env(var, env);
            if (!env)
            {
                //ft_free_arrays_i(env_buffer, -1);
                return (EXIT_FAILURE);
            }
            //ft_free_arrays_i(env_buffer, -1);
        }
        i++;
    }
    return (EXIT_SUCCESS);
}