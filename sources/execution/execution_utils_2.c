/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/09 14:01:10 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ADD STRNDUP TO LIBFT

void	replace_and_free(char **old_str, char *new_str)
{
	if (*old_str != new_str)
	{
		free(*old_str);
		*old_str = new_str;
	}
}

void	ft_error_exit(const char *format, const char *filename)
{
	ft_error(format, filename, strerror(errno));
	exit(EXIT_FAILURE);
}

// Utility function to split the key and value from an assignment string
void	split_assignment(const char *assignment, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(assignment, '=');
	if (!equal_sign)
	{
		*key = NULL;
		*value = NULL;
		return ;
	}
	*key = strndup(assignment, equal_sign - assignment);
	*value = ft_strdup(equal_sign + 1);
}

// Function to get the variable name starting at position i in the string.
char	*get_var_name(const char *str, int i)
{
	int	len;

	len = 0;
	while (ft_isalnum(str[i + len]) || str[i + len] == '_')
		len++;
	return (strndup(str + i, len));
}

// This function retrieves a value for a key from the global environment array
char	*get_value_from_global_env(char **env, const char *key)
{
	size_t	key_len;
	int		i;

	i = 0;
	key_len = strlen(key);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (ft_strdup(env[i] + key_len + 1));
		i++;
	}
	return (NULL);
}
