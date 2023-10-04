/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:38:34 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/04 12:20:23 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append(t_command_parser **head, t_token **token, int is_pipe_before)
{
	t_command_parser	*node;
	t_command_parser	*last_node;

	node = malloc(sizeof(t_command_parser));
	if (!node)
		return ;
	node->command = fill_command(token);
	if (!node->command)
		return (free(node)); // implementer la gestion d'erreur
	last_node = *head;
	node->next = NULL;
	if (*head == NULL)
	{
		node->previous = NULL;
		*head = node;
		return; // implementer la gestion d'erreur
	}
	while (last_node->next != NULL)
		last_node = last_node->next;
	last_node->next = node;
	node->previous = last_node;
	if (is_pipe_before == 1)
		node->previous->command->pipe_after = 1;
	return ;
}

t_command	*init_command()
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->command = NULL;
	command->command_args = NULL;
	command->pipe_after = 0;
	//command->pipe_before = 0;
	command->nb_args = 0;
	command->in_redirection = NULL;
	command->out_redirection = NULL;
	return (command);
}
