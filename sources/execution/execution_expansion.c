/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/18 01:06:46 by hebernar         ###   ########.fr       */
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
	if (strcmp(arg, "$?") == 0)
	{
		char buffer[12];  // Enough to hold int value
		int len = sprintf(buffer, "%d", g_signal);
		buffer[len] = '\0';
		return (strdup(buffer));
	}
	else if (arg[0] == '$')
	{
		const char *var_name = arg + 1;
		for (int i = 0; env[i]; i++)
		{
			if (strncmp(env[i], var_name, strlen(var_name)) == 0 && env[i][strlen(var_name)] == '=')
				return (strdup(env[i] + strlen(var_name) + 1));
		}
	}
	return (strdup(arg));
}

void	expand_command_arguments(t_command *cmd, char **env)
{
	for (int i = 0; cmd->command_args[i]; i++)
	{
		char *expanded_arg = expand_variable(cmd->command_args[i], env);
		free(cmd->command_args[i]);
		cmd->command_args[i] = expanded_arg;
	}
}
