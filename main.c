/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:24:46 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/04 12:22:05 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


void    print_prompt(void)
{

	char    cwd[SIZE_PATH];
	char    **split_cwd;
	int     i;
	int     num_directories;

	getcwd(cwd, SIZE_PATH);
	split_cwd = ft_split(cwd, '/');
	if (!split_cwd)
		return ;
	i = 0;
	num_directories = 0;
	while (split_cwd[num_directories])
		num_directories++;
	while(i < num_directories)
	{
		if (i == num_directories - 1)
		{
			ft_printf("\e[36m\e[1m%s\e[0m", split_cwd[i]);
			break;
		}
		ft_printf("\e[36m%s/\e[0m", split_cwd[i]);
		i++;
	}
	ft_printf("\e[32m\e[1m\n> \e[0m");
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
	t_env	*environment;

	(void)argv;
	(void)argc;
	environment = fill_env(env);
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
		print_parser(first_command);
		execute_command(first_command, env);
	}
	return (0);
}