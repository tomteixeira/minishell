/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:21:14 by toteixei          #+#    #+#             */
/*   Updated: 2023/09/19 16:03:40 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    print_parser(t_command_parser *head);

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

char    **fill_args(t_token **token, int *nb_arg)
{
    t_token **copy;
    char    **args;
    int     i;
    int     j;
    
    copy = token;
    i = 0;
    while (copy[i] && copy[i]->type != TOKEN_PIPE)
    {
        i++;
        (*nb_arg)++;
    }
    copy = token;
    i = 0;
    j = 0;
    args = malloc(*nb_arg * sizeof(char *));
    if (!args)
        return (NULL);
    while (copy[i] && copy[i]->type != TOKEN_PIPE)
    {
        args[j++] = ft_strdup(copy[i]->value);
        if (!args[j - 1])
            return (NULL); // NE pas oublier de free en cascade
        i++;
    }
    //free(copy);
    return (args);
}

t_command   *fill_command(t_token **token)
{
    t_command   *command;
    t_token     **buffer;
    int         i;

    i = 0;
    buffer = token;
    command = init_command(buffer[i]);
    if (!command)
        return (NULL);
    i++;
    if (buffer[i] && (buffer[i]->type == TOKEN_COMMAND
        || buffer[i]->type == TOKEN_OPTION || buffer[i]->type == TOKEN_VARIABLE))
        command->command_args = fill_args(&buffer[i], &command->nb_args);
    if (!command->command_args)
        return (free(command->command), free(command), NULL);
    return (command);
}

// t_command_parser *parse_tokens(t_token **token)
// {
//     t_command_parser    *first_command;
//     t_command_parser    *buffer;
//     t_command_parser    *buffer2;
//     int                 i;
    
//     i = 0;
//     if (token[i] == NULL)
//         return (NULL);
//     first_command = new_node(token);
//     if (!first_command)
//         return (NULL);
//     buffer = first_command;
//     while (token[i] != NULL)
//     {
//         if (token[i]->type == TOKEN_PIPE && token[i + 1])
//         {
//             i++;
//             first_command->next = new_node(&token[i]);
//             if (!first_command->next)
//                 return (NULL);  // NE pas oublier de free en cascade;
//             if (first_command->previous == NULL)
//                 buffer = first_command;
//             buffer2 = first_command;
//             first_command = first_command->next;
//             first_command->previous = buffer2;
//         }
//         i++;
//     }
//     print_parser(buffer);
//     return (buffer); // NE pas oublier de free les buffers
// }

t_command_parser *parse_tokens(t_token **token)
{
    t_command_parser    *first_command;
    int                 i;
    
    i = 0;
    if (token[i] == NULL)
        return (NULL);
    first_command = NULL;
    append(&first_command, token);
    if (!first_command)
        return (NULL);
    while (token[i] != NULL)
    {
        if (token[i]->type == TOKEN_PIPE && token[i + 1])
        {
          i++;
          append(&first_command, &token[i]);
        }
        i++;
    }
    print_parser(first_command);
    return (first_command); // NE pas oublier de free les buffers
}



void    print_parser(t_command_parser *head)
{
    t_command_parser    *buffer;
    int                 i;

    buffer = head;
    while (buffer->next)
    {
        printf("command : %s\n", buffer->command->command);
        i = 0;
        while (i < buffer->command->nb_args)
        {
            printf("Argument %d : %s\n", i, buffer->command->command_args[i]);
            i++;
        }
        printf("\n");
        buffer = buffer->next;
    }
}
