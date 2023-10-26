/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/26 10:10:37 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len = strlen(s1) + strlen(s2) + strlen(s3) + 1;
	str = malloc(len);
	if (!str)
		return (NULL);
	strcpy(str, s1);
	strcat(str, s2);
	strcat(str, s3);
	return (str);
}

static char	*expand_variable(const char *arg, char **env)
{
	char		buffer[12];
	int			len;
	const char	*var_name;
	int			i;

	if (strcmp(arg, "$?") == 0)
	{
		len = sprintf(buffer, "%d", g_signal);
		buffer[len] = '\0';
		return (strdup(buffer));
	}
	else if (arg[0] == '$')
	{
		var_name = arg + 1;
		i = 0;
		while (env[i])
		{
			if (strncmp(env[i], var_name,
					strlen(var_name)) == 0 && env[i][strlen(var_name)] == '=')
				return (strdup(env[i] + strlen(var_name) + 1));
			i++;
		}
		return (strdup(""));
	}
	return (strdup(arg));
}

static char *remove_double_quotes(const char *str)
{
    char *new_str;
    int i, j;

    new_str = (char *)malloc(strlen(str) + 1);
    if (!new_str)
        return (NULL);

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] != '\"')
        {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0';

    return new_str;
}

static char *remove_single_quotes(const char *str)
{
    char *new_str;
    int i, j;

    new_str = (char *)malloc(strlen(str) + 1);
    if (!new_str)
        return (NULL);

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] != '\'')
        {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0';

    return new_str;
}

void expand_command_arguments(t_command *cmd, char **env)
{
    int i;
    char *expanded_arg;
    char *no_double_quotes_arg;
    char *no_single_quotes_arg;

    i = 0;
    if (!cmd->command_args)
        return;

    while (cmd->command_args[i])
    {
        no_double_quotes_arg = remove_double_quotes(cmd->command_args[i]);
        expanded_arg = expand_variable(no_double_quotes_arg, env);
        free(no_double_quotes_arg);
        no_single_quotes_arg = remove_single_quotes(expanded_arg);
        free(expanded_arg);
        free(cmd->command_args[i]);
        cmd->command_args[i] = no_single_quotes_arg;
        i++;
    }
}

