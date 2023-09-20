/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:21:14 by toteixei          #+#    #+#             */
/*   Updated: 2023/09/20 15:22:14 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    print_parser(t_command_parser *head);

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

t_command   *fill_command(t_token **token, int is_pipe_before)
{
    t_command   *command;
    t_token     **buffer;
    int         i;

    if (token[0]->type = TOKEN_REDIRECTION)
        fill_redirection(token, &command);
    i = 0;
    buffer = token;
    command = init_command(buffer[i]);
    if (!command)
        return (NULL);
    i++;
    if (buffer[i] && (buffer[i]->type == TOKEN_WORD
        || buffer[i]->type == TOKEN_STRING || buffer[i]->type == TOKEN_VARIABLE))
    {
        command->command_args = fill_args(&buffer[i], &command->nb_args);
        if (!command->command_args)
            return (free(command->command), free(command), NULL);
    }
    if (is_pipe_before == 1)
        command->pipe_before = 1;
    return (command);
}

t_command_parser *parse_tokens(t_token **token)
{
    t_command_parser    *first_command;
    int                 i;
    
    i = 0;
    if (token[i] == NULL)
        return (NULL);
    first_command = NULL;
    append(&first_command, token, 0);
    if (!first_command)
        return (NULL);
    while (token[i] != NULL)
    {
        if (token[i]->type == TOKEN_PIPE && token[i + 1])
        {
          i++;
          append(&first_command, &token[i], 1);
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
    while (buffer)
    {
        if (buffer->command->pipe_before == 1)
            printf(" | pipe before\n");
        printf("command : %s\n", buffer->command->command);
        i = 0;
        while (i < buffer->command->nb_args)
        {
            printf("Argument %d : %s\n", i, buffer->command->command_args[i]);
            i++;
        }
        if (buffer->command->pipe_after == 1)
            printf(" | pipe after\n");
        printf("\n");
        buffer = buffer->next;
    }
}
