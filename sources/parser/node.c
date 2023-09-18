/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:38:34 by toteixei          #+#    #+#             */
/*   Updated: 2023/09/18 17:19:45 by toteixei         ###   ########.fr       */
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

t_command	*init_node(t_token *token)
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
	node->command = fill_command(token);
	node->previous = NULL;
	node->next = NULL;
	return (node);
}