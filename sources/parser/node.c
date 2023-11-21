/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:38:34 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/21 00:12:42 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append(t_command_parser **head, t_tokenlist **token, int is_pipe_before)
{
	t_command_parser	*node;
	t_command_parser	*last_node;

	node = malloc(sizeof(t_command_parser));
	if (!node)
		return ;
	node->command = fill_command(token);
	if (!node->command)
		return (free(node));
	last_node = *head;
	node->next = NULL;
	if (*head == NULL)
	{
		node->previous = NULL;
		*head = node;
		return ;
	}
	while (last_node->next != NULL)
		last_node = last_node->next;
	last_node->next = node;
	node->previous = last_node;
	if (is_pipe_before == 1)
		node->previous->command->pipe_after = 1;
	return ;
}

t_command	*init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->cargs = NULL;
	command->pipe_after = 0;
	command->nb_args = 0;
	command->in_redirection = NULL;
	command->out_redirection = NULL;
	return (command);
}
