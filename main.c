/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:24:46 by toteixei          #+#    #+#             */
/*   Updated: 2023/08/30 13:55:23 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void    print_prompt(void)
{
    
    char cwd[SIZE_PATH];
    
    getcwd(cwd, SIZE_PATH);
    ft_printf("> %s\nMinishell>> ", cwd);
}

char *read_line(void)
{
    char *line;

    line = get_next_line(0);
    if (!line)
        return (NULL);
    return (line);
}

int main(int argc, char **argv, char **env)
{
    char *line;
    t_token **tokens;
    //t_ast_tree  *root;
    
    (void)argv;
    (void)env;
    (void)argc;
    while (42)
    {
        print_prompt();
        line = read_line();
        if (!line)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        tokens = lexer(line);
        if (!tokens)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    }
    return (0);
}