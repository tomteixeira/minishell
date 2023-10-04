/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:25:38 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/04 18:36:24 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include "../libft/libft.h"
# include "structure.h"
# include <string.h>
# include <stdarg.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

# define SIZE_PATH 4096
//int g_signal;

/*Env functions*/
t_env	*fill_env(char **env);

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
int		check_parsing(t_token **token);

/*Parser functions*/
t_command_parser	*new_node(t_token **token);
t_command			*init_command();
t_command   		*fill_command(t_token **token);
t_command_parser 	*parse_tokens(t_token **token);
void				append(t_command_parser **head, t_token **token, int is_pipe_before);
void	            fill_redirection(t_token **token, t_command **command, int *i);
void    			print_parser(t_command_parser *head);

/*Execution functions*/
void execute_command(t_command_parser *first_command, char **env);

#endif