/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/21 00:14:35 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Utility function to check if there is an assignment
int	is_assignment(const char *cmd)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (*cmd)
	{
		if (*cmd == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*cmd == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (*cmd == '=' && !in_single_quote && !in_double_quote)
			return (1);
		cmd++;
	}
	return (0);
}

// Utility to remove an element from a char **
char	**remove_from_list(char **list, char *arg, int i)
{
	int		count;
	char	**new_list;
	int		j;

	count = 0;
	if (!list || !arg)
		return (list);
	while (list[count] != NULL)
		count++;
	new_list = malloc(sizeof(char *) * count);
	if (!new_list)
		return (NULL);
	j = 0;
	while (i < count)
	{
		if (ft_strcmp(list[i], arg) == 0)
			free(list[i]);
		else
			new_list[j++] = list[i];
		i++;
	}
	new_list[j] = NULL;
	free(list);
	return (new_list);
}

// Utility function to execute builtins
int	execute_builtin(t_minishell **c, char ***env)
{
	if (!(*c)->first_command->command->cargs)
		return (0);
	if (ft_strcmp((*c)->first_command->command->cargs[0], "echo") == 0)
		return (g_signal = echo((*c)->first_command->command->cargs, *env), 1);
	else if (ft_strcmp((*c)->first_command->command->cargs[0], "cd") == 0)
		return (g_signal = cd((*c)->first_command->command->cargs, *env), 1);
	else if (ft_strcmp((*c)->first_command->command->cargs[0], "pwd") == 0)
		return (g_signal = pwd((*c)->first_command->command->cargs, *env), 1);
	else if (ft_strcmp((*c)->first_command->command->cargs[0], "export") == 0)
		return (g_signal = export((*c)->first_command->command->cargs, env), 1);
	else if (ft_strcmp((*c)->first_command->command->cargs[0], "unset") == 0)
		return (g_signal = unset((*c)
				->first_command->command->cargs, env, c), 1);
	else if (ft_strcmp((*c)->first_command->command->cargs[0], "env") == 0)
		return (g_signal = ft_env(NULL, *env), 1);
	else if (ft_strcmp((*c)->first_command->command->cargs[0], "exit") == 0)
	{
		ft_exit(c, (*c)->first_command->command->cargs, *env);
		return (g_signal);
	}
	return (0);
}

// Initialize Execution Context
void	init_execution_context(int *prev_pipe_read_fd, int *pipefd)
{
	*prev_pipe_read_fd = -1;
	pipefd[0] = -1;
	pipefd[1] = -1;
}

int	is_builtin(char *cmd)
{
	int					i;
	static const char	*builtins[] = {
		"echo",
		"export",
		"cd",
		"env",
		"exit",
		"pwd",
		"unset",
		NULL
	};

	if (!cmd)
		return (0);
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd, (char *)builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
