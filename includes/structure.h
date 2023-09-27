/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/09/27 11:33:36 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef enum 
{
    TOKEN_PIPE,
    TOKEN_COMMAND,
    TOKEN_STRING,
	TOKEN_VARIABLE,
	TOKEN_WORD,
	TOKEN_REDIRECTION,
    TOKEN_HEREDOC,
} t_tokentype;

typedef enum
{
    R_IN,
    R_OUT,
    A_R_OUT,
}   t_redirection_type;

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

typedef struct s_redirection
{
    t_redirection_type      type;
    char                    *file;
    struct s_redirection    *next;
    
}   t_redirection;

typedef struct s_command
{
    char                    *command;
    char                    **command_args;
    int                     pipe_after;
    int                     nb_args;
    struct s_redirection    *in_redirection;
    struct s_redirection    *out_redirection;
}   t_command;

typedef struct s_command_parser
{
    t_command           *command;
    struct s_command_parser    *next;
    struct s_command_parser    *previous;
}   t_command_parser;


#endif