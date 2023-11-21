/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:10:48 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/21 15:36:15 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_unfinished_pipe(t_tokenlist **t)
{
	char		*line;
	t_tokenlist	*new_tokens;

	new_tokens = NULL;
	while (1)
	{
		//handle_heredoc_signal();
		//write(STDIN_FILENO, "pipe> ", 6);
		//line = get_next_line(STDIN_FILENO);
		line = readline("pipe> ");
		if (!line)
			return (write(2, "\n", 1), 0);
		if (line[0] && line[0] != '\0')
		{
			new_tokens = lexer(line);
			if (!new_tokens)
				return (free(line), 0);
			merge_tokenlist(t, &new_tokens);
			if (check_parsing(t) == 1)
				return (free(line), 1);
		}
	}
	return (free(line), 1);
}

void	print_syntax_error(char *token)
{
	printf("bash: syntax error near unexpected token `%s'\n", token);
}

int	check_parsing_bis(t_tokenlist *cur)
{
	t_tokenlist	*n;

	n = cur->next;
	if (cur->token->type == T_RED && n->token->type != T_WORD
		&& n->token->type != T_STR && n->token->type != T_VAR)
		return (print_syntax_error(n->token->value), 0);
	if (cur->token->type == T_PIP && n->token->type == T_PIP)
		return (print_syntax_error(n->token->value), 0);
	return (1);
}

int	check_parsing(t_tokenlist **t)
{
	t_tokenlist	*cur;
	t_tokenlist	*n;

	cur = *t;
	if (!cur)
		return (0);
	if (cur->token && cur->token->type == T_PIP)
		return (print_syntax_error(cur->token->value), 0);
	while (cur)
	{
		n = cur->next;
		if (!cur->token)
			return (0);
		if (!n && cur->token->type == T_PIP)
			return (handle_unfinished_pipe(t));
		if (!n && (cur->token->type == T_RED))
			return (print_syntax_error("newline"), 0);
		if (n)
			if (!check_parsing_bis(cur))
				return (0);
		cur = n;
	}
	return (1);
}
