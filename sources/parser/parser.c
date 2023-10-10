/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:21:14 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/10 17:11:33 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void    print_parser(t_command_parser *head);

char    **fill_args(t_tokenlist **token, int *nb_arg)
{
    t_tokenlist *buffer;
    char        **args;
    int         j;

    buffer = *token;
    while (buffer && buffer->token->type != T_PIP && buffer->token->type != T_RED)
    {
        (*nb_arg)++;
        buffer = buffer->next;
    }
    j = 0;
    args = malloc((*nb_arg + 1) * sizeof(char *));
    if (!args)
        return (NULL);
    while ((*token) && (*token)->token->type != T_PIP && (*token)->token->type != T_RED)
    {
        args[j++] = ft_strdup((*token)->token->value);
        if (!args[j - 1])
            return (ft_free_arrays_i(args, j - 1), NULL);
        (*token) = (*token)->next;
    }
    args[j] = NULL;
    return (args);
}

t_command   *fill_command(t_tokenlist **token) // gestion de la memoire
{
    t_command   *command;

    command = init_command();
    if (!command)
        return (NULL);
    while ((*token) && (*token)->token->type == T_RED)
    {
        fill_redirection(token, &command);
        (*token) = (*token)->next->next;
    }
    if (!(*token))
        return (command);
    if ((*token) && ((*token)->token->type == T_WORD
        || (*token)->token->type == T_STR || (*token)->token->type == T_VAR))
    {
        command->command_args = fill_args(token, &command->nb_args);
        if (!command->command_args)
            return (free(command), NULL);
    }
    while ((*token) && (*token)->token->type == T_RED)
    {
        fill_redirection(token, &command);
        (*token) = (*token)->next->next;
    }
    return (command);
}

t_command_parser *parse_tokens(t_tokenlist *token)
{
    t_command_parser    *first_command;

    if (token == NULL)
        return (NULL);
    first_command = NULL;
    append(&first_command, &token, 0);
    if (!first_command)
        return (NULL);
    while (token != NULL)
    {
        if (token->token->type == T_PIP && token->next)
        {
            token = token->next;
            append(&first_command, &token, 1);
            if (token == NULL)
                break ;
        }
        token = token->next;
    }
    if (token != NULL)
        return (NULL);
    return (first_command);
}



void    print_parser(t_command_parser *head)
{
    t_command_parser    *buffer;
    int                 i;

    buffer = head;
    while (head)
    {
        // if (head->command->pipe_before == 1)
        //     printf(" | pipe before\n");
        i = 0;
        while (i < head->command->nb_args)
        {
            printf("Argument %d : %s\n", i, head->command->command_args[i]);
            i++;
        }
        if (head->command->in_redirection != NULL)
        {
            while (head->command->in_redirection)
            {
                printf("Infile redirection : %s\n", head->command->in_redirection->file);
                head->command->in_redirection = head->command->in_redirection->next;
            }
        }
        if (head->command->out_redirection != NULL)
        {
            while (head->command->out_redirection)
            {
                printf("Outfile redirection : %s\n", head->command->out_redirection->file);
                head->command->out_redirection = head->command->out_redirection->next;
            }
        }
        if (head->command->pipe_after == 1)
            printf(" | pipe after\n");
        printf("\n");
        head = head->next;
    }
    head = buffer;
}

// t_command   *fill_command(t_tokenlist **token) // gestion de la memoire
// {
//     t_command   *command;
//     t_token     **buffer;
//     int         i;

//     i = 0;
//     buffer = token;
//     command = init_command();
//     if (!command)
//         return (NULL);
//     while (buffer[i] && buffer[i]->type == T_RED)
//     {
//         fill_redirection(buffer, &command, &i);
//         i += 2;
//     }
//     if (!buffer[i])
//         return (command);
//     if (buffer[i] && (buffer[i]->type == T_WORD
//         || buffer[i]->type == T_STR || buffer[i]->type == T_VAR))
//     {
//         command->command_args = fill_args(&buffer[i], &command->nb_args);
//         if (!command->command_args)
//             return (free(command), NULL);
//         i += command->nb_args;
//     }
//     while (buffer[i] && buffer[i]->type == T_RED)
//     {
//         fill_redirection(buffer, &command, &i);
//         i += 2;
//     }
//     return (command);
// }

// char    **fill_args(t_token **token, int *nb_arg)
// {
//     t_token **copy;
//     char    **args;
//     int     i;
//     int     j;

//     copy = token;
//     i = 0;
//     while (copy[i] && copy[i]->type != T_PIP && copy[i]->type != T_RED)
//     {
//         i++;
//         (*nb_arg)++;
//     }
//     copy = token;
//     i = 0;
//     j = 0;
//     args = malloc((*nb_arg) * sizeof(char *) + 1);
//     if (!args)
//         return (NULL);
//     while (copy[i] && copy[i]->type != T_PIP && copy[i]->type != T_RED)
//     {
//         args[j++] = ft_strdup(copy[i]->value);
//         if (!args[j - 1])
//             return (NULL); // NE pas oublier de free en cascade
//         i++;
//     }
//     args[j] = NULL;
//     return (args);
// }