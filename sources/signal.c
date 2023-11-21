/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:01:58 by tomteixeira       #+#    #+#             */
/*   Updated: 2023/11/21 16:40:15 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	interrupt_exec_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		printf("\n");
	}
}

void	quit_exec_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		g_signal = 131;
		printf("Quit (core dumped)\n");
	}
}

void	interrupt_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_exec_signal(void)
{
	signal(SIGINT, interrupt_exec_signal);
	signal(SIGQUIT, quit_exec_signal);
}

void	handle_input_signal(void)
{
	signal(SIGINT, interrupt_signal);
	signal(SIGQUIT, SIG_IGN);
}
