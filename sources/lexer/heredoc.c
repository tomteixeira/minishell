/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:15:39 by toteixei          #+#    #+#             */
/*   Updated: 2023/09/28 16:07:16 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*heredoc_loop(char *eof, int eof_len)
{
	char	*heredoc;
	char	*buffer;
	char	*line;
	
	heredoc = NULL;
	while(ft_strncmp(line, eof, eof_len) != 1)
	{
		printf("heredoc> ");
		line = get_next_line(0);
		buffer = heredoc;
		heredoc = ft_strjoin(buffer, line);
	}
	free(buffer);
}

t_token *heredoc_token(t_lexer **lexer)
{
    char	*eof;
	char	*heredoc;
    int		eof_len;
	int		i;
    
    while((*lexer)->input_string[(*lexer)->position]
		&& ((*lexer)->input_string[(*lexer)->position] == '<'
        || ft_iswhitespace((*lexer)->input_string[(*lexer)->position])))
        (*lexer)->position++;
	eof_len = 0;
	i = (*lexer)->position;
	while((*lexer)->input_string[(*lexer)->position]
        && ft_iswhitespace((*lexer)->input_string[i++]))
		eof_len++;
	eof = malloc((eof_len + 1) * sizeof(char));
	if (!eof)
		return (NULL); // implementation de la gestion d'erreur
	i = -1;
	while (++i < eof_len)
		eof[i] = (*lexer)->input_string[(*lexer)->position++];
	eof[i] = '\0';
	heredoc = heredoc_loop(eof, eof_len);
	return (create_heredoc_token(heredoc));
}