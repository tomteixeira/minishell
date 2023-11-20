/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:22:57 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/20 15:46:26 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exit_print_err(const char *arg)
{
	printf("minishell: exit: %s: numeric argument required\n", arg);
	return (g_signal = 2);
}

static int	ft_exit_args(char **args)
{
	int			is_num;
	const char	*arg = args[1];

	is_num = 1;
	if (arg[0] == '-' || arg[0] == '+')
		arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg++))
		{
			is_num = 0;
			break ;
		}
	}
	if (is_num)
		g_signal = ft_atoi(args[1]);
	else
		exit_print_err(args[1]);
	return (g_signal);
}

void	ft_exit(t_minishell **cur, char **args, char **env)
{
	(void)env;
	if (!args[1])
	{
		g_signal = 0;
	}
	else if (!args[2])
	{
		g_signal = ft_exit_args(args);
	}
	else
	{
		if (ft_isdigit(args[1][0]) || (args[1][0] == '-'
				&& ft_isdigit(args[1][1])))
		{
			printf("minishell: exit: too many arguments\n");
			g_signal = 1;
			return ;
		}
		exit_print_err(args[1]);
	}
	ft_free(cur, 1);
	exit(g_signal);
}
