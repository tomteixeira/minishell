/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:24:46 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/04 19:11:07 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"



char	*custom_prompt()
{
    char cwd[PATH_MAX];
    char *cwd_color;
    char *reset_color;
	
	cwd_color = "\033[36m";
	reset_color = "\033[0m";
	getcwd(cwd, PATH_MAX);
	printf("\033[0;33m\033[0m%s%s%s", cwd_color, cwd, reset_color);
	printf("\e[32m\e[1m\n> \e[0m");
    return (readline(""));
}

char *read_line(void)
{
	char *line;

	line = custom_prompt();
	if (!line)
		return (NULL);
	add_history(line);
	return (line);
}

int main(int argc, char **argv, char **env)
{
	char *line;
	t_token **tokens;
	t_command_parser  *first_command;
	//t_env	*environment;

	(void)argv;
	(void)argc;
    (void)env;
	//environment = fill_env(env);
	line = NULL;
	tokens = NULL;
	first_command = NULL;
	while (42)
	{
		//print_prompt();
		line = read_line();

		if (line)
		{
			tokens = lexer(line);
			free(line);
		}

		if (tokens)
			first_command = parse_tokens(tokens);
		if (first_command)
		{
			print_parser(first_command);
			execute_command(first_command, env);
            //free_parsing(&tokens, &first_command)
			tokens = NULL;
			first_command = NULL;
		}
	}
	return (0);
}