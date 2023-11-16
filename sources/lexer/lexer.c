/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:39:04 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/16 17:38:46 by tomteixeira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*init_lexer(const char *input)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->input_string = input;
	lexer->position = 0;
	return (lexer);
}

t_token	*get_next_token_bis(t_lexer *lexer, char cur)
{
	if (cur == '|')
		return (create_token(T_PIP, "|", &lexer));
	else if (cur == '>' || cur == '<')
		return (create_token(T_RED, &lexer->input_string[lexer->position],
				&lexer));
	else if (ft_isprint(cur))
		return (create_token(T_WORD, &lexer->input_string[lexer->position],
				&lexer));
	return (NULL);
}

t_token	*get_next_token(t_lexer *lexer)
{
	char	cur;

	while (lexer->input_string[lexer->position] != '\0')
	{
		cur = lexer->input_string[lexer->position];
		if (cur == ' ' || cur == '\t' || cur == '\n')
		{
			lexer->position++;
			continue ;
		}
		if (cur == '|' || ft_isprint(cur) || cur == '\'' || cur == '\"'
			|| cur == '$' || cur == '<' || cur == '>')
			return (get_next_token_bis(lexer, cur));
		lexer->position++;
	}
	return (NULL);
}

void	append_token(t_tokenlist **head, t_token *token)
{
	t_tokenlist	*last_node;
	t_tokenlist	*node;

	node = malloc(sizeof(t_tokenlist));
	if (!node)
		return ;
	node->token = token;
	node->next = NULL;
	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	last_node = *head;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = node;
	return ;
}

t_tokenlist	*lexer(char *command_line)
{
	t_lexer		*lexer;
	t_tokenlist	*head;
	t_tokenlist	*cur;
	t_token		*token;

	lexer = init_lexer(command_line);
	if (!lexer)
		return (NULL);
	head = NULL;
	while (1)
	{
		token = get_next_token(lexer);
		if (token == NULL)
			break ;
		if (head == NULL)
			(append_token(&head, token), cur = head);
		else
			(append_token(&head, token), cur = cur->next);
	}
	if (lexer->input_string[lexer->position] != '\0')
		return (free(lexer), free_tokenlist(head), NULL);
	free(lexer);
	if (check_parsing(&head) == 0)
		return (free_tokenlist(head), NULL);
	return (head);
}
