/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:22:53 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/25 14:40:23 by tomteixeira      ###   ########.fr       */
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

int    modify_existant_var(char *var, char ***env)
{
    char    *var_key;
    int     i;

	i = 0;
	var_key = ft_substr(var, 0, ft_strlenchr(var, '='));
    if (!var_key)
        return (0);
    while ((*env)[i])
    {
        if (ft_strncmp(var_key, (*env)[i], ft_strlen(var_key)) == 0)
        {
            (*env)[i] = ft_strdup(var);
            if (!(*env)[i])
				return (0);
        }
		i++;
    }
	return (1);
}

int    check_existant_var(char *var)
{
    char    *var_key;
    char    *var_check;

    var_key = ft_substr(var, 0, ft_strlenchr(var, '='));
    if (!var_key)
        return (0);
    printf("%s\n", var);
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
    new_env[env_count] = ft_strdup(var);
    if (!new_env[i])
        return (ft_free_arrays_i(new_env, i), NULL);
    new_env[env_count + 1] = NULL;
    return (new_env);
}

int     export(char **args, char ***env)
{
    int     i;
    char    *var;
    
    if (!args[1])
        return (export_no_args(*env), EXIT_SUCCESS);
    i = 1;
    while (args[i])
    {
        var = NULL;
        var = set_var(args[i]);
        if (var && check_existant_var(var))
        {
            printf("existant var\n");
			modify_existant_var(var, env);
			if (!*env)
                return (EXIT_FAILURE);
		}
        else if (var)
        {
            printf("new_var\n");
            *env = set_new_env(var, *env);
            if (!*env)
                return (EXIT_FAILURE);
        }
        i++;
    }
    return (EXIT_SUCCESS);
}