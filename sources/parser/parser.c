/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:21:14 by toteixei          #+#    #+#             */
/*   Updated: 2023/09/18 17:24:40 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_if_node *parse_if()
// {
    
// }

// t_while_node *parse_while()
// {
    
// }

// t_redirection_node *parse_redirection_node()
// {
    
// }

// t_pipe_sequence_node *parse_pipe_sequence()
// {
    
// }

// t_sequence_node *parse_sequence_node()
// {
    
// }

// t_pipe_node *parse_pipe_node()
// {
    
// }

// t_command_node *parse_command()
// {
    
// }

// t_ast_tree  *parse_sequence(t_token **token)
// {
//     t_ast_tree  *root;

//     root = new_node(TOKEN_ROOT);
//     if (!root)
//         return (NULL);
    
// }

// t_ast_tree  *parse_lexer(t_token *token)
// {
//     return (parse_sequence(&token));
// }

char    **fill_args(t_token **token, int nb_arg)
{
    t_token **copy;
    char    **args;
    int     i;
    
    copy = token;
    while ((*copy)->type != TOKEN_PIPE && *copy)
    {
        (*copy)++;
        nb_arg++;
    }
    copy = token;
    i = 0;
    args = malloc(nb_arg * sizeof(char *));
    if (!args)
        return (NULL);
    while ((*copy)->type != TOKEN_PIPE && *copy)
    {
        args[i++] = ft_strdup((*copy)->value);
        if (!args[i - 1])
            return (NULL); // NE pas oublier de free en cascade
        (*copy)++;
    }
    free(copy);
    return (args);
}

t_command   *fill_command(t_token **token)
{
    t_command   *command;

    command = init_command(*token);
    if (!command)
        return (NULL);
    (*token)++;
    if ((*token)->type == TOKEN_COMMAND)
        command->command_args = fill_args(token, command->nb_args);
    if (!command->command_args)
        return (free(command->command), free(command), NULL);
    
    return (command);
}

t_command_parser *parse_tokens(t_token **token)
{
    t_command_parser    *first_command;

    
    return (first_command);
}
