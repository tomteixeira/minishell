/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:39:04 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/15 11:22:38 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	print_token_list(t_tokenlist *list);

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
        return (create_token(T_PIP, "|", &lexer));
	else if (cur == '\"' || cur == '\'')
        return (create_token(T_STR, 
			&lexer->input_string[lexer->position], &lexer));
	else if (cur == '>' || cur == '<')
		return (create_token(T_RED, 
			&lexer->input_string[lexer->position], &lexer));
	else if (ft_isprint(cur))
        return (create_token(T_WORD, 
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
		if (cur == '|' || ft_isprint(cur) || cur == '\'' || 
			cur == '\"' || cur == '$' || cur == '<' || cur == '>')
			return (get_next_token_bis(lexer, cur));
        lexer->position++;
    }
    return (NULL);
}

void		append_token(t_tokenlist **head, t_token *token)
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
    t_lexer 	*lexer;
	t_tokenlist *head;
	t_tokenlist	*cur;
	t_token		*token;
	
	lexer = init_lexer(command_line);
	if (!lexer)
		return (NULL);
	head = NULL;
	cur = NULL;
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
		return (NULL);
	free(lexer);
	if (check_parsing(head) == 0)
		return (NULL);
	return (head);
}

void	print_token_list(t_tokenlist *list)
{
    while (list != NULL)
	{
        printf("Token Value: %s\n", list->token->value);
        list = list->next;
    }
}

// t_token	**lexer(char *command_line) 
// {
//     t_lexer *lexer;
// 	lexer = init_lexer(command_line);
//     int	i = 0;
//     t_token **token;
// 	token = malloc(sizeof(t_token *));
// 	if (!token)
// 		return (NULL);
// 	while (1) 
//   	{
// 		token[i] = get_next_token(lexer);
// 		if (!token[i])
// 			break ;
//         // if (!token[i])
// 		// 	return (free_tokens(token, i), NULL);
//         i++;
//         token = realloc(token, (i + 1) * sizeof(t_token *));
//         // if (!token[i])
// 		// 	return (free_tokens(token, i), NULL);
//     }
// 	free(lexer);
// 	token[i] = NULL;
// 	if (check_parsing(&token[0]) == 0)
// 		return (NULL);
// 	return (&token[0]);
// }