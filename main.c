/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:24:46 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/26 15:44:07 by tomteixeira      ###   ########.fr       */
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
	if (g_signal != 0)
		printf("\033[31m - %d", g_signal);
	printf("\e[32m\e[1m \n❯ \e[0m");
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

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int main(int argc, char **argv, char **env)
{
	char *line;
	t_tokenlist *tokens;
	t_command_parser  *first_command;

	(void)argv;
	(void)argc;
	line = NULL;
	tokens = NULL;
	first_command = NULL;
	signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		line = read_line();
		if (!line)
			exit(0);
		if (line)
			tokens = lexer(line);
		if (tokens)
			first_command = parse_tokens(tokens);
		if (first_command)
		{
//			print_parser(first_command);
			execute_command(first_command, &env);
		}
		ft_free(&line, &tokens, &first_command);
	}
	return (0);
}
