/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/15 12:41:15 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_piping(t_command *cmd, int *pipefd)
{
	if (cmd->pipe_after)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

static char	*extract_key(const char *env_str)
{
	char	*key;

	key = ft_strndup(env_str, ft_strchr(env_str, '=') - env_str);
	return (key);
}

static int	key_in_local_env(t_env_var *local_env, const char *key)
{
	while (local_env != NULL)
	{
		if (ft_strcmp(local_env->key, (char *)key) == 0)
			return (1);
		local_env = local_env->next;
	}
	return (0);
}

static void	add_to_local_env(t_env_var **local_env,
								const char *key,
								const char *value)
{
	t_env_var	*new_var;

	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
		exit(EXIT_FAILURE);
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = *local_env;
	*local_env = new_var;
}

void	add_missing_keys(t_env_var **local_env_var, char **global_env)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (global_env[i] != NULL)
	{
		key = extract_key(global_env[i]);
		if (!key_in_local_env(*local_env_var, key))
		{
			value = get_value_from_global_env(global_env, key);
			add_to_local_env(local_env_var, key, value);
			free(value);
		}
		free(key);
		i++;
	}
}
