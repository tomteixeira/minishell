/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:24:46 by toteixei          #+#    #+#             */
/*   Updated: 2023/09/19 10:50:30 by toteixei         ###   ########.fr       */
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
    t_command_parser  *first_command;
    
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
        free(line);
        if (!tokens)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        first_command = parse_tokens(tokens);
        if (!first_command)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    }
    return (0);
}