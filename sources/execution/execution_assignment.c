/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_assignment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/05 12:58:50 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Utility function to split the key and value from an assignment string
static void split_assignment(const char *assignment, char **key, char **value)
{
	char *equal_sign;

	equal_sign = strchr(assignment, '=');
	if (!equal_sign)
	{
		*key = NULL;
		*value = NULL;
		return ;
	}
	*key = strndup(assignment, equal_sign - assignment); // ADD FUNCTION LIBFT
	*value = ft_strdup(equal_sign + 1);
}

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

static void update_env(char ***env, char *key, char *value)
{
    size_t key_len;
    size_t new_size;
    int i;

    i = 0;
    key_len = strlen(key);
    while ((*env)[i] != NULL)
    {
        if (strncmp((*env)[i], key, key_len) == 0 && (*env)[i][key_len] == '=')
        {
            free((*env)[i]);
            new_size = key_len + strlen(value) + 2;
            (*env)[i] = malloc(new_size);
            snprintf((*env)[i], new_size, "%s=%s", key, value);
            return;
        }
        i++;
    }
    new_size = key_len + strlen(value) + 2;
    (*env)[i] = malloc(new_size);
    snprintf((*env)[i], new_size, "%s=%s", key, value);
    (*env)[i+1] = NULL;
}

static void	update_local_env(t_env_var **env_var, char *key, char *value)
{
	t_env_var *current;
	t_env_var *new_var;

	new_var = NULL;
	current = *env_var;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return;
		}
		current = current->next;
	}
	new_var = malloc(sizeof(t_env_var));
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = *env_var;
	*env_var = new_var;
}

static int	update_global_env(char ***env, t_env_var **env_var, char *key, char *value)
{
	(void)env_var;
	if (key_in_env(*env, key))
	{
//		printf("key in env\n");
		update_env(env, key, value);
//		printf("Updating global env\n");
		update_local_env(env_var, key, value);
//		printf("Updating local env\n");
		return (1);
	}
	return (0);
}

// Utility function to handle assignments $> a=b
int	handle_assignments(t_command_parser **current, char ***env, t_env_var **env_var)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (!(*current)->command->command_args)
		return (0);
	if (is_assignment((*current)->command->command_args[0])
		&& (*current)->command->command_args[1]
		== NULL && (*current)->next == NULL)
	{
		split_assignment((*current)->command->command_args[0], &key, &value);
//		printf("key: %s\n", key);
//		printf("value: %s\n", value);
		if (update_global_env(env, env_var, key, value))
			;
		else
			update_local_env(env_var, key, value);
		free(key);
		free(value);
		return (1);
	}
	else if (is_assignment((*current)->command->command_args[0]))
		(*current)->command->command_args
			= remove_from_list((*current)->command->command_args,
				(*current)->command->command_args[0]);
	return (0);
}