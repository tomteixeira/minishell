/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:10:48 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/04 16:03:29 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	check_directory(t_token *token)
// {
	
// }

void	print_syntax_error(char *token)
{
	printf("bash: syntax error near unexpected token `%s'\n", token);
}

int	check_parsing(t_token **token)
{
	int	i;

	i = 0;
	if (!token[0])
		return (0);
	if (!token[1] && (token[0]->type == TOKEN_REDIRECTION || token[0]->type == TOKEN_PIPE))
	{
		print_syntax_error("newline");
		return (0);
	}
	while (token[i])
	{
		if (token[i + 1] && ((token[i]->type == TOKEN_REDIRECTION ||  token[i]->type == TOKEN_PIPE)
			&& (token[i + 1]->type == TOKEN_REDIRECTION || token[i + 1]->type == TOKEN_PIPE)))
		{
			print_syntax_error(token[i]->value);
			return (0);
		}
		if (token[i]->type == TOKEN_REDIRECTION && (!token[i + 1] || token[i + 1]->type != TOKEN_WORD))
		{
			print_syntax_error(token[i]->value);
			return (0);
		}
		i++;
	}
	
	return (1);
}