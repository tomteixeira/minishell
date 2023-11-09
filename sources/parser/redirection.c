/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:43:59 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/17 15:42:25 by tomteixeira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	append_redirection(t_redirection **head, t_redirection_type type,
		t_tokenlist **token)
{
	t_redirection	*node;
	t_redirection	*buffer;

	node = malloc(sizeof(t_redirection));
	if (!node)
		return (0);
	node->file = ft_strdup((*token)->next->token->value);
	if (!node->file)
	{
		free(node);
		return (0);
	}
	node->type = type;
	node->next = NULL;
	if (*head == NULL)
	{
		*head = node;
		return (1);
	}
	buffer = *head;
	while (buffer->next != NULL)
		buffer = buffer->next;
	buffer->next = node;
	return (1);
}

int	fill_redirection_bis(t_tokenlist **token, t_command **command)
{
	if ((*token)->token->value[0] == '>')
	{
		if (append_redirection(&(*command)->out_redirection, R_OUT,
				&(*token)) == 0)
			return (0);
	}
	else if ((*token)->token->value[0] == '<')
	{
		if (append_redirection(&(*command)->in_redirection, R_IN,
				&(*token)) == 0)
			return (0);
	}
	return (1);
}

int	fill_redirection(t_tokenlist **token, t_command **command)
{
	if (!(*token) || (((*token)->next->token->type != T_WORD
				&& (*token)->next->token->type != T_STR
				&& (*token)->next->token->type != T_VAR)))
		return (0);
	if ((*token)->token->value[0] == '>' && (*token)->token->value[1]
		&& (*token)->token->value[1] == '>')
	{
		if (append_redirection(&(*command)->out_redirection, A_R_OUT,
				&(*token)) == 0)
			return (0);
	}
	else if ((*token)->token->value[0] == '<' && (*token)->token->value[1]
		&& (*token)->token->value[1] == '<')
	{
		if (append_redirection(&(*command)->in_redirection, HEREDOC,
				&(*token)) == 0)
			return (0);
	}
	else if ((*token)->token->value[0] == '<'
		|| (*token)->token->value[0] == '>')
		return (fill_redirection_bis(token, command));
	return (1);
}
