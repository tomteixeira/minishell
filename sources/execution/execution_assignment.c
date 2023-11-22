/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_assignment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/22 12:32:16 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	key_in_env(char **env, char *key)
{
	size_t	key_len;
	int		i;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (1);
		i++;
	}
	return (0);
}

static void	update_env(char ***env, char *key, char *value)
{
	size_t	key_len;
	int		i;

	key_len = ft_strlen(key);
	i = 0;
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], key, key_len) == 0 &&
			(*env)[i][key_len] == '=')
		{
			update_existing_env_var(env, key, value, i);
			return ;
		}
		i++;
	}
	add_new_env_var(env, key, value, i);
}

/*
static void	update_env(char ***env, char *key, char *value, int i)
{
	size_t		key_len;
	size_t		value_len;
	t_env_var	*current;
	t_env_var	*new_var;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], key,
			key_len) == 0 && (*env)[i][key_len] == '=')
		{
			free((*env)[i]);
			(*env)[i] = malloc(key_len + value_len + 2);
			if (!(*env)[i])
				exit(EXIT_FAILURE);
			ft_strcpy((*env)[i], key);
			(*env)[i][key_len] = '=';
			ft_strcpy((*env)[i] + key_len + 1, value);
			return ;
		}
		i++;
	}
	(*env)[i] = malloc(key_len + value_len + 2);
	if (!(*env)[i])
		exit(EXIT_FAILURE);
	ft_strcpy((*env)[i], key);
	(*env)[i][key_len] = '=';
	ft_strcpy((*env)[i] + key_len + 1, value);
	(*env)[i + 1] = NULL;
}*/

static void	update_local_env(t_env_var **env_var, char *key, char *value)
{
	t_env_var	*current;
	t_env_var	*new_var;

	new_var = NULL;
	current = *env_var;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_var = malloc(sizeof(t_env_var));
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = *env_var;
	*env_var = new_var;
}

static int	update_global_env(char ***env,
								t_env_var **env_var,
								char *key,
								char *value)
{
	(void)env_var;
	if (key_in_env(*env, key))
	{
		update_env(env, key, value);
		update_local_env(env_var, key, value);
		return (1);
	}
	return (0);
}

// Utility function to handle assignments $> a=b
int	handle_assignments(t_command_parser **current,
						char ***env,
						t_env_var **env_var)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (!(*current)->command->cargs)
		return (0);
	if (is_assignment((*current)->command->cargs[0])
		&& (*current)->command->cargs[1] == NULL && (*current)->next == NULL)
	{
		split_assignment((*current)->command->cargs[0], &key, &value);
		if (update_global_env(env, env_var, key, value))
			;
		else
			update_local_env(env_var, key, value);
		free(key);
		free(value);
		return (1);
	}
	else if (is_assignment((*current)->command->cargs[0]))
		(*current)->command->cargs = remove_from_list((*current)->command->cargs,
				(*current)->command->cargs[0], 0);
	return (0);
}
