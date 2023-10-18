/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:22:53 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/18 15:58:25 by tomteixeira      ###   ########.fr       */
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

int    check_existant_var(char *var)
{
    char    *var_key;
    char    *var_check;

    var_key = ft_substr(var, 0, ft_strchr(var, '='));
    if (!var_key)
        return (0);
    var_check = getenv(var_key);
    if (!var_check)
        return (free(var_key), 0);
    free(var_key);
        return (1);
    
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
    
    if (!args[1])
        return (export_no_args(env), EXIT_SUCCESS);
    i = 1;
    while (args[i])
    {
        var = NULL;
        var = set_var(args[i]);
        if (var && check_existant_var(var))
        {
            
        }
        if (var)
        {
            env = set_new_env(var, env);
            if (!env)
                return (EXIT_FAILURE);
        }
        i++;
        free(var);
    }
    return (EXIT_SUCCESS);
}