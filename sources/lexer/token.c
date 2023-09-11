/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:07:49 by toteixei          #+#    #+#             */
/*   Updated: 2023/08/30 11:54:49 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*string_token(t_lexer **lexer)
{
	t_token *token;
	char	cur;
	int		len;
	int		i;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	len = string_len(lexer);
	token->value = malloc((len + 1) * sizeof(char));
	if (!token->value)
		return (NULL);
	token->type = TOKEN_STRING;
	i = 0;
	while (len > 0 && (*lexer)->input_string[(*lexer)->position])
	{
		cur = (*lexer)->input_string[(*lexer)->position];
		token->value[i++] = cur;
		(*lexer)->position++;
		len--;
	}
	token->value[i] = '\0';
	return (token);
}

t_token	*command_token(t_lexer **lexer)
{
	t_token *token;
	char	cur;
	int		len;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	len = command_len(lexer);
	token->value = malloc((len + 1) * sizeof(char));
	if (!token->value)
		return (NULL);
	token->type = TOKEN_COMMAND;
	len = 0;
	while ((*lexer)->input_string[(*lexer)->position] != '\0' && 
			ft_isalpha((*lexer)->input_string[(*lexer)->position]))
	{
        cur = (*lexer)->input_string[(*lexer)->position];
		token->value[len] = cur;
		(*lexer)->position++;
		len++;
	}
	token->value[len] = '\0';
	return (token);
}

t_token	*option_variable_token(t_tokentype type, t_lexer **lexer)
{
	t_token *token;
	char	cur;
	int		len;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	len = option_len(lexer);
	token->value = malloc((len + 1) * sizeof(char));
	if (!token->value)
		return (NULL);
	token->type = type;
	len = 1;
	token->value[0] = (*lexer)->input_string[(*lexer)->position++];
	while ((*lexer)->input_string[(*lexer)->position] != '\0' && 
			ft_isalpha((*lexer)->input_string[(*lexer)->position]))
	{
        cur = (*lexer)->input_string[(*lexer)->position];
		token->value[len] = cur;
		(*lexer)->position++;
		len++;
	}
	token->value[len] = '\0';
	return (token);
}

t_token	*redirection_token(t_lexer **lexer)
{
	t_token *token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if ((*lexer)->input_string[(*lexer)->position + 1] == '>')
	{
		token->value = ft_strdup(">>");
		(*lexer)->position++;
	}
	else
	{
		token->value = malloc(2 * sizeof(char));
		if (!token->value)
			return (NULL);
		token->value[0] = (*lexer)->input_string[(*lexer)->position];
		token->value[1] = '\0';
	}
	(*lexer)->position++;
	token->type = TOKEN_REDIRECTION;
	return (token);
}

t_token *create_token(t_tokentype type, const char *value, t_lexer **lexer)
{
    t_token *token;
    
	if (type == TOKEN_COMMAND)
		return (command_token(lexer));
	else if (type == TOKEN_STRING)
		return (string_token(lexer));
	else if (type == TOKEN_OPTION ||type == TOKEN_VARIABLE)
		return (option_variable_token(type, lexer));
	else if (type == TOKEN_REDIRECTION)
		return (redirection_token(lexer));
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
    token->value = ft_strdup(value);
	(*lexer)->position++;
    return (token);
}