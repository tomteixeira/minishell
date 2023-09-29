/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:25:38 by toteixei          #+#    #+#             */
/*   Updated: 2023/09/28 13:17:38 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include "../libft/libft.h"
# include "structure.h"
# include <string.h>
# include <stdarg.h>
# include <stdbool.h>

# define SIZE_PATH 4096
//int g_signal;


/*Lexer fonctions*/
t_token **lexer(char *command_line);
int		command_len(t_lexer **lexer);
int		string_len(t_lexer **lexer);
int     option_len(t_lexer **lexer);
t_token	*string_token(t_lexer **lexer);
t_token	*command_token(t_lexer **lexer);
t_token	*option_variable_token(t_tokentype type, t_lexer **lexer);
t_token	*redirection_token(t_lexer **lexer);
t_token *create_token(t_tokentype type, const char *value, t_lexer **lexer);
t_token *heredoc_token(t_lexer **lexer);
int		ft_word_char(int c);

/*Parser functions*/
//t_ast_tree	*new_node(t_tokentype token_type);
t_command_parser	*new_node(t_token **token);
t_command			*init_command();
t_command   		*fill_command(t_token **token);
t_command_parser 	*parse_tokens(t_token **token);
void				append(t_command_parser **head, t_token **token, int is_pipe_before);
void	            fill_redirection(t_token **token, t_command **command, int *i);

#endif