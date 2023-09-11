/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/08/30 13:47:46 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H


typedef enum {
    TOKEN_PIPE,
    TOKEN_SEMICOLON,
    TOKEN_COMMAND,
    TOKEN_STRING,
	TOKEN_VARIABLE,
	TOKEN_OPTION,
	TOKEN_REDIRECTION
} t_tokentype;

typedef struct s_token {
    t_tokentype type;
    char *value;
} t_token;


typedef struct s_lexer {
    const char *input_string;
    size_t position;
} t_lexer;


typedef struct s_command_node {
    
}   t_command_node;

typedef struct s_pipe_node {
    
}   t_pipe_node;

typedef struct s_redirection_node {
    
}   t_redirection_node;

typedef struct s_if_node {
    
}   t_if_node;

typedef struct s_while_node {
    
}   t_while_node;

typedef struct s_ast_tree {
    char    *type;
    union
    {
        t_command_node      *command_node;
        t_pipe_node         *pipe_node;
        t_redirection_node  *redirection_node;
        t_if_node           *if_node;
        t_while_node        *while_node;
    } u_data;
    struct t_ast_tree   *right;
    struct t_ast_tree   *left;
}   t_ast_tree;

#endif