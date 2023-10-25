/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/25 15:09:38 by tomteixeira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Utility function to check if there is an assignment
int	is_assignment(const char *cmd)
{
	if (ft_strchr(cmd, '='))
		return (1);
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
		return (g_signal = cd(cmd->command_args, *env), 1);
	else if (ft_strcmp(cmd->command_args[0], "pwd") == 0)
		return (g_signal = pwd(cmd->command_args, *env), 1);
	else if (ft_strcmp(cmd->command_args[0], "export") == 0)
		return (g_signal = export(cmd->command_args, env), 1);
	else if (ft_strcmp(cmd->command_args[0], "unset") == 0)
		return (g_signal = unset(cmd->command_args, env), 1);
	// else if (ft_strcmp(cmd->command_args[0], "env") == 0)
	// 	return (g_signal = env(*env), 1);
	// else if (ft_strcmp(cmd->command_args[0], "exit") == 0)
	// 	return (g_signal = exit(cmd->command_args), 1);
	return (0);
}

// Initialize Execution Context
void	init_execution_context(t_command_parser **current,
	int *prev_pipe_read_fd, t_command_parser *first_command)
{
	*current = first_command;
	*prev_pipe_read_fd = -1;
}
