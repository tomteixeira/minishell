/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:22:57 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/08 15:08:30 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int exit_print_err(const char *arg)
{
	printf("minishell: exit: %s: numeric argument required\n", arg);
	return (g_signal = 2);
}

static int ft_exit_args(char **args)
{
	int is_num = 1;
	const char *arg = args[1];

	if (arg[0] == '-' || arg[0] == '+')
		arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg++))
		{
			is_num = 0;
			break;
		}
	}
	if (is_num)
		g_signal = ft_atoi(args[1]);
	else
		exit_print_err(args[1]);
	return (g_signal);
}

void ft_exit(char **args, char **env)
{
	(void)env;
	printf("exit\n");
	if (!args[1])
	{  // No argument after exit
		g_signal = 0;  // Use the last command's exit status
	}
	else if
	(!args[2])
	{  // One argument after exit
		g_signal = ft_exit_args(args);
	}
	else
	{  // More than one argument after exit
		if (ft_isdigit(args[1][0]) || (args[1][0] == '-' && ft_isdigit(args[1][1])))
		{
			printf("minishell: exit: too many arguments\n");
			g_signal = 1;  // Set error status but do not exit
			return;
		}
		exit_print_err(args[1]);
		exit(g_signal);
	}
}
