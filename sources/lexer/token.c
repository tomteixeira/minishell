/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:07:49 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/05 17:39:58 by toteixei         ###   ########.fr       */
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
	token->type = T_STR;
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

t_token	*word_token(t_lexer **lexer)
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
	token->type = T_WORD;
	len = 0;
	while ((*lexer)->input_string[(*lexer)->position] != '\0' && 
			ft_word_char((*lexer)->input_string[(*lexer)->position]))
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
	if ((*lexer)->input_string[(*lexer)->position + 1] &&
		(*lexer)->input_string[(*lexer)->position + 1] == '>')
	{
		token->value = ft_strdup(">>");
		(*lexer)->position++;
	}
	else if ((*lexer)->input_string[(*lexer)->position + 1] == '<')
	{
		token->value = ft_strdup("<<");
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
	token->type = T_RED;
	return (token);
}

t_token *create_token(t_tokentype type, const char *value, t_lexer **lexer)
{
    t_token *token;
    
	if (type == T_WORD)
		return (word_token(lexer));
	else if (type == T_STR)
		return (string_token(lexer));
	else if (type == T_RED)
		return (redirection_token(lexer));
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
    token->value = ft_strdup(value);
	(*lexer)->position++;
    return (token);
}