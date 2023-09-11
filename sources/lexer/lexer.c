/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:39:04 by toteixei          #+#    #+#             */
/*   Updated: 2023/08/30 14:01:08 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_tokens(t_token **token, int i) // A tester
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(token[j]->value);
		free(token[j]);
		j++;
	}
}

t_lexer *init_lexer(const char *input)
{
    t_lexer *lexer = malloc(sizeof(t_lexer));
    lexer->input_string = input;
    lexer->position = 0;
    return lexer;
}

t_token	*get_next_token_bis(t_lexer *lexer, char cur)
{
	if (cur == '|')
        return (create_token(TOKEN_PIPE, "|", &lexer));
	else if (cur == ';')
        return (create_token(TOKEN_SEMICOLON, ";", &lexer));
	else if (ft_isalpha(cur))
        return (create_token(TOKEN_COMMAND, 
			&lexer->input_string[lexer->position], &lexer));
	else if (cur == '\"' || cur == '\'')
        return (create_token(TOKEN_STRING, 
			&lexer->input_string[lexer->position], &lexer));
	else if (cur == '-')
		return (create_token(TOKEN_OPTION, 
			&lexer->input_string[lexer->position], &lexer));
	else if (cur == '$')
		return (create_token(TOKEN_VARIABLE, 
			&lexer->input_string[lexer->position], &lexer));
	else if (cur == '>' || cur == '<')
		return (create_token(TOKEN_REDIRECTION, 
			&lexer->input_string[lexer->position], &lexer));
	return (NULL);
}

t_token *get_next_token(t_lexer *lexer)
{
    char	cur;
	
	while (lexer->input_string[lexer->position] != '\0')
	{
        cur = lexer->input_string[lexer->position];

        if (cur == ' ' || cur == '\t' || cur == '\n') {
            lexer->position++;
            continue;
        }
		if (cur == '|' || cur == ';' || ft_isalpha(cur) || cur == '\'' || 
			cur == '\"' || cur == '-' || cur == '$' || cur == '<' || cur == '>')
			return (get_next_token_bis(lexer, cur));
        lexer->position++;
    }
    return (NULL);
}

t_token	**lexer(char *command_line) 
{
    t_lexer *lexer;
	lexer = init_lexer(command_line);
    int	i = 0;
    t_token **token = malloc(sizeof(t_token *));
	if (!token)
		return (0);
	token[0] = get_next_token(lexer);
	if (!token[0])
		return (NULL);
    while (token[i] != NULL)
	{
        ft_printf("Token: %d, Value: %s\n", token[i]->type, token[i]->value);
        token[++i] = get_next_token(lexer);
		// if (!token[i])
		// 	return (free_tokens(token, i), NULL);
    }
	free(lexer);
	return (token);
    return 0;
}