/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:10:48 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/05 17:48:49 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int check_parsing(t_tokenlist *token) 
{
    t_tokenlist *cur;
	t_tokenlist	*n; //next_node
	//t_token		*current_token;
	t_token		*nt;
	
	cur = token;
    if (!cur)
        return (0);
    while (cur)
	{
		n = cur->next;
        if (!cur->token)
            return (0);
        if (!n && (cur->token->type == T_RED || cur->token->type == T_PIP))
            return (print_syntax_error("newline"), 0);
        if (cur->token->type == T_WORD && !n)
            check_exit(cur->token->value);
        if (n)
		{
            nt = n->token;
            if ((cur->token->type == T_RED || cur->token->type == T_PIP)
                && (nt->type == T_RED || nt->type == T_PIP))
                return (print_syntax_error(cur->token->value), 0);
            if (cur->token->type == T_RED && (nt->type != T_WORD))
                return (print_syntax_error(cur->token->value), 0);
        }
        cur = n;
    }
    return (1);
}

// int	check_parsing(t_token **token)
// {
// 	int	i;

// 	i = 0;
// 	if (!token[0])
// 		return (0);
// 	if (!token[1] && (token[0]->type == T_RED || token[0]->type == T_PIP))
// 	{
// 		print_syntax_error("newline");
// 		return (0);
// 	}
// 	if (token[0]->type == T_WORD && !token[1])
// 		check_exit(token[0]->value);
// 	while (token[i])
// 	{
// 		if (token[i + 1] && ((token[i]->type == T_RED ||  token[i]->type == T_PIP)
// 			&& (token[i + 1]->type == T_RED || token[i + 1]->type == T_PIP)))
// 		{
// 			print_syntax_error(token[i]->value);
// 			return (0);
// 		}
// 		if (token[i]->type == T_RED && (!token[i + 1] || token[i + 1]->type != T_WORD))
// 		{
// 			print_syntax_error(token[i]->value);
// 			return (0);
// 		}
// 		i++;
// 	}
	
// 	return (1);
// }