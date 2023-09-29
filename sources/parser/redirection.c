/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:43:59 by toteixei          #+#    #+#             */
/*   Updated: 2023/09/29 14:18:00 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **copy_char_array(char **src) {
    if (!src) return NULL;
    int count = 0;
    while (src[count]) {
        count++;
    }
    char **dest = (char **)malloc((count + 1) * sizeof(char *));
    if (!dest) return NULL;
    for (int i = 0; i < count; i++) {
        dest[i] = strdup(src[i]);
        if (!dest[i]) {
            for (int j = 0; j < i; j++) {
                free(dest[j]);
            }
            free(dest);
            return NULL;
        }
    }
    dest[count] = NULL;
    return (dest);
}

void    append_redirection(t_redirection **head, t_redirection_type type,
                            t_token **token)
{
    t_redirection   *node;
    t_redirection   *buffer;
    node = malloc(sizeof(t_redirection));
    if (!node)
        return ; //implementer la gestion d'erreur
    node->file = ft_strdup(token[1]->value);
    if (!node->file)
        return ; // implementer la gestion d'erreur
    node->type = type;
    node->next = NULL;
    if (*head == NULL)
    {
        *head = node;
        return ; // implementer la gestion d'erreur
    }
    buffer = *head;
    while (buffer->next != NULL)
        buffer = buffer->next;
    buffer->next = node;
    return ;
}

void	fill_redirection(t_token **token, t_command **command, int *i)
{
    if (!token[*i + 1] || ((token[*i + 1]->type != TOKEN_WORD
        && token[*i + 1]->type != TOKEN_STRING && token[*i + 1]->type != TOKEN_VARIABLE)))
        return ; // implementer la gestion d'erreur, fonction generale d'erreur
    if (token[*i]->value[0] == '>' && token[*i]->value[1] && token[*i]->value[1] == '>')
        append_redirection(&(*command)->out_redirection, A_R_OUT, &token[*i]);
    else if (token[*i]->value[0] == '>')
        append_redirection(&(*command)->out_redirection, R_OUT, &token[*i]);
    else if (token[*i]->value[0] == '<')
        append_redirection(&(*command)->in_redirection, R_IN, &token[*i]);
}