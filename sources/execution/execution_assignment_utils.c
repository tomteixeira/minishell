/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_assignment_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/14 19:31:55 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_existing_env_var(char ***env,
	const char *key, const char *value, int i)
{
	size_t	key_len;
	size_t	value_len;

	value_len = ft_strlen(value);
	key_len = ft_strlen(key);
	free((*env)[i]);
	(*env)[i] = malloc(key_len + value_len + 2);
	if (!(*env)[i])
		exit(EXIT_FAILURE);
	ft_strcpy((*env)[i], key);
	(*env)[i][key_len] = '=';
	ft_strcpy((*env)[i] + key_len + 1, value);
}

void	add_new_env_var(char ***env, const char *key,
	const char *value, int i)
{
	size_t	key_len;
	size_t	value_len;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	(*env)[i] = malloc(key_len + value_len + 2);
	if (!(*env)[i])
		exit(EXIT_FAILURE);
	ft_strcpy((*env)[i], key);
	(*env)[i][key_len] = '=';
	ft_strcpy((*env)[i] + key_len + 1, value);
	(*env)[i + 1] = NULL;
}
