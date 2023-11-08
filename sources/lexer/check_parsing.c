/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:10:48 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/08 19:32:30 by tomteixeira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tokenlist(t_tokenlist *head)
{
	t_tokenlist *buffer;

	buffer = head;
	while (buffer)
	{
		printf("%s\n", buffer->token->value);
		buffer = buffer->next;
	}
}

void	merge_tokenlist(t_tokenlist **head_a, t_tokenlist **head_b)
{
	t_tokenlist	*lastnode_a;

	lastnode_a = *head_a;
	while (lastnode_a->next)
		lastnode_a = lastnode_a->next;
	lastnode_a->next = *head_b;
}

int		handle_unfinished_pipe(t_tokenlist **t)
{
	char	*line;
	t_tokenlist	*new_tokens;

	new_tokens = NULL;
	while (1)
	{
		write(STDOUT_FILENO, "pipe> ", 6);
		line = get_next_line(STDERR_FILENO);
		if (!line)
			return (0);
		if (line[0] && line[0] != '\n')
		{
			new_tokens = lexer(line);
			if (!new_tokens)
				return (0);
			merge_tokenlist(t, &new_tokens);
			if (check_parsing(t) == 1)
				return (1);
		}
	}
	return (1);
}

void	check_exit(char *token)
{
	if (ft_strncmp(token, "exit", ft_strlen(token)) == 0)
	{
		exit(0);
	}
	return ;
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
		if (cur->token->type == T_WORD && !n)
			check_exit(cur->token->value);
		if (n)
			if (!check_parsing_bis(cur))
				return (0);
		cur = n;
	}
	return (1);
}
