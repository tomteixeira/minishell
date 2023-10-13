/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/13 12:38:55 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Utility function to join two strings with a '/'
static char	*join_with_slash(const char *s1, const char *s2)
{
	int		len1;
	int		len2;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 2);
	if (!result)
		return (NULL);
	strcpy(result, s1);
	result[len1] = '/';
	strcpy(result + len1 + 1, s2);
	return (result);
}

// Check Immediate Command Access
static char	*check_direct_command_access(const char *command)
{
	if (access(command, F_OK | X_OK) == 0)
		return (ft_strdup(command));
	return (NULL);
}

// Tokenize Path
void	get_next_path_token(char **token_start)
{
	char	*token_end;

	token_end = *token_start;
	while (*token_end && *token_end != ':')
		token_end++;
	if (*token_end == ':')
	{
		*token_end = '\0';
		*token_start = token_end + 1;
	}
	else
		*token_start = NULL;
}

// Try Paths
static char	*try_paths(const char *command, char *path_copy)
{
	char	*token_start;
	char	*possible_command;
	char	*current_path;

	token_start = path_copy;
	while (token_start && *token_start)
	{
		current_path = token_start;
		get_next_path_token(&token_start);
		possible_command = join_with_slash(current_path, command);
		if (!possible_command)
			return (NULL);
		if (access(possible_command, F_OK) != -1)
		{
			free(path_copy);
			return (possible_command);
		}
		free(possible_command);
	}
	free(path_copy);
	return (NULL);
}

char	*find_command_in_path(const char *command)
{
	char	*direct_access_result;
	char	*path;
	char	*path_copy;

	direct_access_result = check_direct_command_access(command);
	if (direct_access_result)
		return (direct_access_result);
	path = getenv("PATH");
	if (!path)
		return (NULL);
	path_copy = ft_strdup(path);
	if (!path_copy)
		return (NULL);
	return (try_paths(command, path_copy));
}