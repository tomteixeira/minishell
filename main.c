/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:24:46 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/08 17:23:31 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Initialisation env var

t_env_var *create_env_var(const char *env_str)
{
	char *key_value_pair;
	char *delimiter;
	t_env_var *var;

	var = (NULL);
	key_value_pair = ft_strdup(env_str);
	delimiter = ft_strchr(key_value_pair, '=');
	if (!delimiter)
	{
		free(key_value_pair);
		return (NULL);
	}

	*delimiter = '\0';
	var = malloc(sizeof(t_env_var));
	if (!var)
	{
		free(key_value_pair);
		return (NULL);
	}
	var->key = key_value_pair;
	var->value = delimiter + 1;
	var->next = NULL;
	return (var);
}

void init_env_var(t_env_var **env_var, char **env)
{
	t_env_var	*current_var;
	t_env_var	*previous_var;
	int			i;

	if (!env || !*env)
	{
		*env_var = NULL;
		return;
	}
	i = 0;
	current_var = NULL;
	previous_var = NULL;
	while (env[i] != NULL)
	{
		current_var = create_env_var(env[i]);
		if (!current_var)
			continue;
		if (previous_var)
			previous_var->next = current_var;
		else
			*env_var = current_var;
		previous_var = current_var;
		i++;
	}
}

// Fin initialization


char	*custom_prompt()
{
	char	cwd[PATH_MAX];
	char	*cwd_color;
	char	*reset_color;

	cwd_color = "\033[36m";
	reset_color = "\033[0m";
	getcwd(cwd, PATH_MAX);
	printf("\033[0;33m\033[0m%s%s%s", cwd_color, cwd, reset_color);
	if (g_signal != 0)
		printf("\033[31m - %d", g_signal);
	printf("\e[32m\e[1m \n❯ \e[0m");
	return (readline(""));
}

char	*read_line(void)
{
	char *line;

	line = custom_prompt();
	if (!line)
		return (NULL);
	add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **env)
{
	char *line;
	t_tokenlist *tokens;
	t_command_parser  *first_command;
	t_env_var *env_var;

	env_var = NULL;
	init_env_var(&env_var, env);
	(void)argv;
	(void)argc;
	line = NULL;
	tokens = NULL;
	first_command = NULL;
	handle_input_signal();
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
			execute_command(first_command, &env, &env_var);
		ft_free(&line, &tokens, &first_command);
	}
	return (0);
}
