/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:01:58 by tomteixeira       #+#    #+#             */
/*   Updated: 2023/11/08 18:27:10 by tomteixeira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    interrupt_exec_signal(int sig)
{
    if (sig == SIGINT)
    {
        g_signal = 130;
        printf("\n");
    }
}

void    quit_exec_signal(int sig)
{
    if (sig == SIGQUIT)
    {
        g_signal = 131;
        printf("minishell: quit process\n");
    }
}

void	interrupt_signal(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_signal = 130;
	}
}

void    handle_exec_signal()
{
    signal(SIGINT, interrupt_exec_signal);
    signal(SIGQUIT, quit_exec_signal);
}

void    handle_input_signal()
{
    signal(SIGINT, interrupt_signal);
	signal(SIGQUIT, SIG_IGN);
}