/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/07 12:16:55 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_sig(int sig_code)
{
	static const char	*siglist[] = {\
		"",
		MS_SIGHUP, MS_SIGINT,
		MS_SIGQUIT, MS_SIGILL,
		MS_SIGTRAP, MS_SIGABRT,
		MS_SIGEMT, MS_SIGFPE,
		MS_SIGKILL, MS_SIGBUS,
		MS_SIGSEGV, MS_SIGSYS,
		MS_SIGPIPE, MS_SIGALRM,
		MS_SIGTERM, MS_SIGURG,
		MS_SIGSTOP, MS_SIGTSTP,
		MS_SIGCONT, MS_SIGCHLD,
		MS_SIGTTIN, MS_SIGTTOU,
		MS_SIGIO, MS_SIGXCPU,
		MS_SIGXFSZ, MS_SIGVTALRM,
		MS_SIGPROF, MS_SIGWINCH,
		MS_SIGINFO, MS_SIGUSR1,
		MS_SIGUSR2
	};

	if (sig_code != 13 && sig_code != 2 && sig_code < 32)
	{
		ft_error("%s: %d\n", siglist[sig_code], sig_code);
	}
}
