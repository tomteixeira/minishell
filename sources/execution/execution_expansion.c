/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/08 15:33:05 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Function to get the variable name starting at position i in the string.
static char *get_var_name(const char *str, int i)
{
	int len = 0;
	while (ft_isalnum(str[i + len]) || str[i + len] == '_')
		len++;
	return strndup(str + i, len);
}

// Function to replace the variable name in the string with its value.
static char *replace_name(const char *str, const char *var_name, const char *var_value, int i)
{
	int name_len = strlen(var_name);
	int value_len = strlen(var_value);
	int str_len = strlen(str);

	char *new_str = malloc(str_len - name_len + value_len + 1);
	if (!new_str)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	strncpy(new_str, str, i);
	new_str[i] = '\0';
	strcat(new_str, var_value);
	strcat(new_str, str + i + name_len + 1);
	return new_str;
}

// Function to get the value of a variable from the environment variable list.
char *get_var_value(t_env_var *env_var, const char *var_name)
{
	while (env_var)
	{
		if (strcmp(env_var->key, var_name) == 0)
		{
			return ft_strdup(env_var->value);
		}
		env_var = env_var->next;
	}
	return strdup("");
}


static char *remove_quotes(const char *str, int flag)
{
	char	*result;
	int		i;
	int		j;
	int		quotes_nb;

	i = 0;
	while (str[i])
	{
		if (flag == 1 && str[i] == '\"')
			quotes_nb++;
		if (flag == 2 && str[i] == '\'')
			quotes_nb++;
		i++;
	}
	result = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		while (flag == 1 && str[i] == '\"')
			i++;
		while (flag == 2 && str[i] == '\'')
			i++;
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

static char *expand_variable(const char *str, t_env_var *env_var, int i)
{
	char *var_name;
	char *var_value;
	char *tmp;

	if (str[i + 1] == '?')
	{
		var_name = strdup("?");
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

static char *expand_argument(const char *str, t_env_var *env_var) {
    int quotes = 0;
    int i = 0;
    char *tmp = ft_strdup(str);
    char *new_tmp;
    char *sub_tmp1;
    char *sub_tmp2;

    if (!tmp) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    while (tmp[i]) {
        if (quotes == 0 && (tmp[i] == '\"'))
            quotes = 1;
        else if (quotes == 0 && (tmp[i] == '\''))
            quotes = 2;
        else if ((quotes == 0 || quotes == 1) && tmp[i] == '$' && tmp[i + 1] != '\0' && tmp[i + 1] != ' ' && tmp[i + 1] != '\"' && tmp[i + 1] != '\'' && (i == 0 || tmp[i - 1] != '\\') && tmp[i + 1] != '=') {
            new_tmp = expand_variable(tmp, env_var, i);
            if (new_tmp != tmp) { // Check if a new string was returned
                free(tmp);
                tmp = new_tmp;
            }
            i = -1;
        } else if (tmp[i] == '\\' && tmp[i + 1] == '$') {
            sub_tmp1 = ft_substr(tmp, 0, i);
            sub_tmp2 = ft_substr(tmp, i + 1, ft_strlen(tmp) - i - 1);
            new_tmp = ft_strjoin(sub_tmp1, sub_tmp2);
            free(sub_tmp1);
            free(sub_tmp2);
            if (new_tmp != tmp) { // Check if a new string was returned
                free(tmp);
                tmp = new_tmp;
            }
            i++; // Move past the dollar sign
        }
        i++;
    }

    if (quotes) {
        new_tmp = remove_quotes(tmp, quotes);
        if (new_tmp != tmp) { // Check if a new string was returned
            free(tmp);
            tmp = new_tmp;
        }
    }

    return tmp;
}



void expand_command_arguments(t_command *cmd, t_env_var *env_var)
{
	int i;
	char *expanded_arg;
	t_redirection *redirection;

	i = 0;
	redirection = cmd->in_redirection;
	while(cmd->in_redirection)
	{
		expanded_arg = expand_argument(cmd->in_redirection->file, env_var);
		free(cmd->in_redirection->file);
		cmd->in_redirection->file = ft_strdup(expanded_arg);
		free(expanded_arg);
		cmd->in_redirection = cmd->in_redirection->next;
	}
	cmd->in_redirection = redirection;
	redirection = cmd->out_redirection;
	while(cmd->out_redirection)
	{
		expanded_arg = expand_argument(cmd->out_redirection->file, env_var);
		free(cmd->out_redirection->file);
		cmd->out_redirection->file = ft_strdup(expanded_arg);
		free(expanded_arg);
		cmd->out_redirection = cmd->out_redirection->next;
	}
	cmd->out_redirection = redirection;
	if (!cmd->command_args)
		return ;
	while (cmd->command_args[i] != NULL)
	{
		expanded_arg = expand_argument(cmd->command_args[i], env_var);
		free(cmd->command_args[i]);
		cmd->command_args[i] = ft_strdup(expanded_arg);
		free(expanded_arg);
		i++;
	}
}
