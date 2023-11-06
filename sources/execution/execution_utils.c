/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/03 08:32:10 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Utility function to check if there is an assignment
int	is_assignment(const char *cmd)
{
	int in_single_quote = 0;
	int in_double_quote = 0;

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
char	**remove_from_list(char **list, char *arg)
{
	int		i;
	int		j;
	int		count;
	char	**new_list;

	count = 0;
	while (list[count])
		count++;
	new_list = malloc((count + 1) * sizeof(char *));
	if (!new_list)
		return (NULL);
	j = 0;
	i = j;
	while (i < count)
	{
		if (ft_strcmp(list[i], arg) != 0)
			new_list[j++] = list[i++];
		else
			free(list[i++]);
	}
	new_list[j] = NULL;
	free(list);
	return (new_list);
}

// Utility function to execute builtins
int	execute_builtin(t_command *cmd, char ***env)
{
	if (!cmd->command_args)
		return (0);
	if (ft_strcmp(cmd->command_args[0], "echo") == 0)
		return (g_signal = echo(cmd->command_args, *env), 1);
	else if (ft_strcmp(cmd->command_args[0], "cd") == 0)
	{
		printf("cd\n");
		return (g_signal = cd(cmd->command_args, *env), 1);
	}
	else if (ft_strcmp(cmd->command_args[0], "pwd") == 0)
		return (g_signal = pwd(cmd->command_args, *env), 1);
	else if (ft_strcmp(cmd->command_args[0], "export") == 0)
	{
		printf("export\n");
		return (g_signal = export(cmd->command_args, env), 1);
	}
	else if (ft_strcmp(cmd->command_args[0], "unset") == 0)
		return (g_signal = unset(cmd->command_args, env), 1);
	else if (ft_strcmp(cmd->command_args[0], "env") == 0)
		return (g_signal = ft_env(NULL, *env), 1);
	// else if (ft_strcmp(cmd->command_args[0], "exit") == 0)
	// 	return (g_signal = exit(cmd->command_args), 1);
	return (0);
}

// Initialize Execution Context
void	init_execution_context(t_command_parser **current,
	int *prev_pipe_read_fd, t_command_parser *first_command, int *pipefd)
{
	*current = first_command;
	*prev_pipe_read_fd = -1;
	pipefd[0] = -1;
	pipefd[1] = -1;
}
