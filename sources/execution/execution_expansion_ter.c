/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_expansion_ter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/17 14:23:58 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_variable(const char *str, t_env_var *env_var, int i)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;

	if (str[i + 1] == '?')
	{
		var_name = ft_strdup("?");
		var_value = ft_itoa(g_signal);
	}
	else
	{
		var_name = get_var_name(str, i + 1);
		var_value = get_var_value(env_var, var_name);
	}
	tmp = replace_name(str, var_name, var_value, i);
	free(var_name);
	free(var_value);
	return (tmp);
}

int	handle_quotes(char current_char, int quotes)
{
	if (quotes == 0 && current_char == '\"')
		return (1);
	else if (quotes == 0 && current_char == '\'')
		return (2);
	return (quotes);
}

char *remove_backslashes(char *str, int *index) {
    if (str == NULL || *index < 0 || *index >= (int)ft_strlen(str)) {
        return NULL;
    }

    if (str[*index] == '\\' && str[*index + 1] != '\0') {
        char *sub_str1 = ft_substr(str, 0, *index);
        char *sub_str2 = ft_substr(str, *index + 1, ft_strlen(str) - *index - 1);
        char *new_str = ft_strjoin(sub_str1, sub_str2);
        free(sub_str1);
        free(sub_str2);
        (*index)++;
        return new_str;
    }

    return str;
}


// Function to replace the variable name in the string with its value.
char	*replace_name(const char *str,
	const char *var_name, const char *var_value, int i)
{
	int		name_len;
	int		value_len;
	int		str_len;
	char	*new_str;

	value_len = ft_strlen(var_value);
	name_len = ft_strlen(var_name);
	str_len = ft_strlen(str);
	new_str = malloc(str_len - name_len + value_len);
	if (!new_str)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(new_str, str, i);
	ft_strcat(new_str, var_value);
	ft_strcat(new_str, str + i + name_len);
	return (new_str);
}

// Function to get the value of a variable from the environment variable list.
char	*get_var_value(t_env_var *env_var, char *var_name)
{
	while (env_var)
	{
		if (ft_strcmp(env_var->key, var_name) == 0)
		{
			return (ft_strdup(env_var->value));
		}
		env_var = env_var->next;
	}
	return (ft_strdup(""));
}
