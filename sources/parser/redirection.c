/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:43:59 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/16 11:31:09 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append_redirection(t_redirection **head, t_redirection_type type,
		t_tokenlist **token)
{
	t_redirection	*node;
	t_redirection	*buffer;

	node = malloc(sizeof(t_redirection));
	if (!node)
		return ;
	node->file = ft_strdup((*token)->next->token->value);
	if (!node->file)
		return ;
	node->type = type;
	node->next = NULL;
	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	buffer = *head;
	while (buffer->next != NULL)
		buffer = buffer->next;
	buffer->next = node;
	return ;
}

void	fill_redirection(t_tokenlist **token, t_command **command)
{
	if (!(*token) || (((*token)->next->token->type != T_WORD
				&& (*token)->next->token->type != T_STR
				&& (*token)->next->token->type != T_VAR)))
		return ;
	if ((*token)->token->value[0] == '>' && (*token)->token->value[1]
		&& (*token)->token->value[1] == '>')
		append_redirection(&(*command)->out_redirection, A_R_OUT, &(*token));
	else if ((*token)->token->value[0] == '<' && (*token)->token->value[1]
		&& (*token)->token->value[1] == '<')
		append_redirection(&(*command)->in_redirection, HEREDOC, &(*token));
	else if ((*token)->token->value[0] == '>')
		append_redirection(&(*command)->out_redirection, R_OUT, &(*token));
	else if ((*token)->token->value[0] == '<')
		append_redirection(&(*command)->in_redirection, R_IN, &(*token));
}
