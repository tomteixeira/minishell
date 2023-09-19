/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/09/19 10:42:39 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef enum 
{
    TOKEN_ROOT,
    TOKEN_PIPE,
    TOKEN_SEMICOLON,
    TOKEN_COMMAND,
    TOKEN_STRING,
	TOKEN_VARIABLE,
	TOKEN_OPTION,
	TOKEN_REDIRECTION,
    TOKEN_HEREDOC,
    TOKEN_FILE,
    TOKEN_WHILE,
    TOKEN_CONDITION,
} t_tokentype;

typedef struct s_token
{
    t_tokentype type;
    char *value;
} t_token;


typedef struct s_lexer
{
    const char *input_string;
    size_t position;
} t_lexer;

typedef struct s_command
{
    char    *command;
    char    **command_args;
    int     pipe_start;
    int     pipe_end;
    int     nb_args;
    
}   t_command;

typedef struct s_command_parser
{
    t_command           *command;
    struct s_command_parser    *next;
    struct s_command_parser    *previous;
}   t_command_parser;


#endif