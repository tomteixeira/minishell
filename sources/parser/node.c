/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:38:34 by toteixei          #+#    #+#             */
/*   Updated: 2023/09/19 16:03:59 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_ast_tree	*new_node(t_tokentype token_type)
// {
//     t_ast_tree	*node;

// 	node = malloc(sizeof(t_ast_tree));
// 	if (!node)
// 		return (NULL);
// 	node->type = token_type;
// 	return (node);
// }

void	append(t_command_parser **head, t_token **token)
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
		return;
	}
	while (last_node->next != NULL)
		last_node = last_node->next;
	last_node->next = node;
	node->previous = last_node;
	return ;
}

t_command	*init_command(t_token *token)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->command = ft_strdup(token->value);
	if (!command->command)
		return (free(command), NULL);
	command->command_args = NULL;
	command->pipe_end = 0;
	command->pipe_start = 0;
	command->nb_args = 0;
	return (command);
}

t_command_parser	*new_node(t_token **token)
{
	t_command_parser	*node;

	node = malloc(sizeof(t_command_parser));
	if (!node)
		return (NULL);
	printf("token %s\n", (*token)->value);
	node->command = fill_command(token);
	if (!node->command)
		return (free(node), NULL);
	node->previous = NULL;
	node->next = NULL;
	return (node);
}