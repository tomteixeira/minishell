/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:21:14 by toteixei          #+#    #+#             */
/*   Updated: 2023/09/14 12:31:58 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_if_node *parse_if()
{
    
}

t_while_node *parse_while()
{
    
}

t_redirection_node *parse_redirection_node()
{
    
}

t_pipe_sequence_node *parse_pipe_sequence()
{
    
}

t_sequence_node *parse_sequence_node()
{
    
}

t_pipe_node *parse_pipe_node()
{
    
}

t_command_node *parse_command()
{
    
}

t_ast_tree  *parse_sequence(t_token **token)
{
    // fonction principale de mon parser qui renvoie root
}

t_ast_tree  *parse_lexer(t_token *token)
{
    return (parse_sequence(&token));
}
