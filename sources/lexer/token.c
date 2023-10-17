/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:07:49 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/17 11:04:25 by tomteixeira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*word_token_bis(t_lexer **lexer, t_token *token, int len)
{
	char	cur;
	char	quote;

	while ((*lexer)->input_string[(*lexer)->position] != '\0'
		&& ft_word_char((*lexer)->input_string[(*lexer)->position]))
	{
		if ((*lexer)->input_string[(*lexer)->position] == '\''
			|| (*lexer)->input_string[(*lexer)->position] == '\"')
		{
			quote = (*lexer)->input_string[(*lexer)->position];
			token->value[len++] = quote;
			(*lexer)->position++;
			while ((*lexer)->input_string[(*lexer)->position]
				&& (*lexer)->input_string[(*lexer)->position] != quote
				&& ft_string_char((*lexer)->input_string[(*lexer)->position]))
			{
				cur = (*lexer)->input_string[(*lexer)->position];
				token->value[len++] = cur;
				(*lexer)->position++;
			}
		}
		cur = (*lexer)->input_string[(*lexer)->position];
		token->value[len++] = cur;
		(*lexer)->position++;
	}
	token->value[len] = '\0';
	return (token);
}

t_token	*word_token(t_lexer **lexer)
{
	t_token	*token;
	int		len;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	len = command_len(lexer);
	token->value = malloc((len + 1) * sizeof(char));
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = T_WORD;
	len = 0;
	return (word_token_bis(lexer, token, len));
}

t_token	*redirection_token_bis(char *value, t_lexer **lexer)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = T_RED;
	(*lexer)->position++;
	return (token);
}

t_token	*redirection_token(t_lexer **lexer)
{
	char	value[2];

	if ((*lexer)->input_string[(*lexer)->position + 1] == '>')
	{
		(*lexer)->position++;
		return (redirection_token_bis(ft_strdup(">>"), lexer));
	}
	else if ((*lexer)->input_string[(*lexer)->position + 1] == '<')
	{
		(*lexer)->position++;
		return (redirection_token_bis(ft_strdup("<<"), lexer));
	}
	else
	{
		value[0] = (*lexer)->input_string[(*lexer)->position];
		value[1] = '\0';
		return (redirection_token_bis(strdup(value), lexer));
	}
	return (NULL);
}

t_token	*create_token(t_tokentype type, const char *value, t_lexer **lexer)
{
	t_token	*token;

	if (type == T_WORD)
		return (word_token(lexer));
	else if (type == T_RED)
		return (redirection_token(lexer));
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	(*lexer)->position++;
	return (token);
}
