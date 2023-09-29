/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/09/29 14:37:13 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Next To Do:
// 1. Implementer < et > et >>
// 2. Gestion d'erreur
// 3. Gestion du Heredoc

// Fonction qui mets la commande et les arguments dans un char ** (necessaire pour execve)
static char	**prepare_args_for_execve(t_command *cmd)
{
	char	**args;
	int		i;

	i = 0;
	args = malloc(sizeof(char *) * (cmd->nb_args + 2));
	if (!args)
	{
		perror("malloc");
		return NULL;
	}
	args[0] = cmd->command;
	while (i < cmd->nb_args)
	{
		args[i + 1] = cmd->command_args[i];
		i++;
	}
	args[cmd->nb_args + 1] = NULL;
	return (args);
}

// Utility function to join two strings with a '/'
static char	*join_with_slash(const char *s1, const char *s2)
{
	int len1;
	int len2;
	char *result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 2);
	if (!result)
		return NULL;
	strcpy(result, s1);
	result[len1] = '/';
	strcpy(result + len1 + 1, s2);
	return result;
}

static char	*find_command_in_path(const char *command)
{
	char *path;
	char *path_copy;
	char *token;
	char *possible_command;

	path = getenv("PATH");
	path_copy = ft_strdup(path);
	token = strtok(path_copy, ":");
	while (token != NULL) {
		possible_command = join_with_slash(token, command);
		if (!possible_command) {
			free(path_copy);
			return NULL;
		}
		if (access(possible_command, F_OK) != -1) {
			free(path_copy);
			return possible_command;
		}
		free(possible_command);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}



void write_error_msg(const char *msg1, const char *msg2) {
	write(STDERR_FILENO, msg1, ft_strlen(msg1));
	if (msg2)
		write(STDERR_FILENO, msg2, ft_strlen(msg2));
	write(STDERR_FILENO, "\n", 1);
}

void execute_command(t_command_parser *first_command, char **env) {
	t_command_parser *current;
	char *full_path;
	char **args;
	pid_t pid;
	int status;

	current = first_command;
	while (current)
	{
		full_path = find_command_in_path(current->command->command);
		if (full_path)
		{
			args = prepare_args_for_execve(current->command);
			if (!args)
			{
				free(full_path);
				return;
			}
			pid = fork();
			if (pid == 0)
			{
			execve(full_path, args, env);
			perror("execve");
			exit(EXIT_FAILURE);
			}
			else if (pid > 0)
			{
				wait(&status);
				if (status != 0)
					write_error_msg("Command exited with an error.", NULL);
			}
			else
				perror("fork");
			free(args);
			free(full_path);
		}
		else
			write_error_msg("Command not found: ", current->command->command);
		current = current->next;
	}
}