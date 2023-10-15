/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/13 09:28:42 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Utility function to write an error message to stderr
void	write_error_msg(const char *msg1, const char *msg2)
{
	write(2, msg1, ft_strlen(msg1));
	if (msg2)
		write(2, msg2, ft_strlen(msg2));
	write(STDERR_FILENO, "\n", 1);
}

// Initialize Execution Context
void	init_execution_context(t_command_parser **current,
	int *num_children, int *prev_pipe_read_fd, t_command_parser *first_command)
{
	*num_children = 0;
	*current = first_command;
	*prev_pipe_read_fd = -1;
}
