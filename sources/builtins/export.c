/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:22:53 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/15 15:49:52 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_existant_var(char *var, char **env)
{
	char	*var_key;
	size_t	key_len;
	int		i;

	i = 0;
	var_key = ft_substr(var, 0, ft_strlenchr(var, '='));
	if (!var_key)
		return (0);
	key_len = ft_strlen(var_key);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_key, key_len) == 0 && env[i][key_len] == '=')
			return (1);
		i++;
	}
	free(var_key);
	return (0);
}

int	modify_existant_var(char *var, char ***env, int i)
{
	char	*var_key;
	size_t	key_len;

	var_key = ft_substr(var, 0, ft_strlenchr(var, '='));
	if (!var_key)
		return (0);
	key_len = ft_strlen(var_key);
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var_key, key_len) == 0 &&
			(*env)[i][key_len] == '=')
		{
			(*env)[i] = ft_strdup(var);
			free(var_key);
			if ((*env)[i])
				return (1);
			else
				return (0);
		}
		i++;
	}
	free(var_key);
	return (0);
}

char	*set_var(char *arg)
{
	int	i;
	int	equal;

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

char	**set_new_env(char *var, char **env)
{
	char	**new_env;
	int		i;
	int		env_count;

	new_env = NULL;
	env_count = 0;
	while (env[env_count])
		env_count++;
	new_env = malloc((env_count + 2) * sizeof(char *));
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

int	export(char **args, char ***env)
{
	int		i;
	char	*var;

	if (!args[1])
		return (export_no_args(*env), EXIT_SUCCESS);
	i = 1;
	while (args[i])
	{
		var = NULL;
		var = set_var(args[i]);
		if (var && check_existant_var(var, *env))
		{
			modify_existant_var(var, env, 0);
			if (!*env)
				return (EXIT_FAILURE);
		}
		else if (var)
		{
			*env = set_new_env(var, *env);
			if (!*env)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
