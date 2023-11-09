/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:24:46 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/09 17:28:35 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int			g_signal = 0;

t_env_var	*create_env_var(const char *env_str)
{
	char		*key_value_pair;
	char		*delimiter;
	t_env_var	*var;

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

void	init_env_var(t_env_var **env_var, char **env)
{
	t_env_var	*current_var;
	t_env_var	*previous_var;
	int			i;

	if (!env || !*env)
	{
		*env_var = NULL;
		return ;
	}
	i = 0;
	current_var = NULL;
	previous_var = NULL;
	while (env[i] != NULL)
	{
		current_var = create_env_var(env[i]);
		if (!current_var)
			continue ;
		if (previous_var)
			previous_var->next = current_var;
		else
			*env_var = current_var;
		previous_var = current_var;
		i++;
	}
}

void	init_variables(t_env_var **env_var, char **line,
		t_tokenlist **tokens, t_command_parser **first_command)
{
	*env_var = NULL;
	*line = NULL;
	*tokens = NULL;
	*first_command = NULL;
}

int	main(int argc, char **argv, char **env)
{
	char				*line;
	t_tokenlist			*tokens;
	t_command_parser	*first_command;
	t_env_var			*env_var;

	(void)argv;
	(void)argc;
	init_variables(&env_var, &line, &tokens, &first_command);
	init_env_var(env_var, env);
	while (42)
	{
		handle_input_signal();
		line = read_line();
		if (!line)
			exit(0);
		if (line)
			tokens = lexer(line);
		if (tokens)
			first_command = parse_tokens(tokens);
		handle_exec_signal();
		if (first_command)
			execute_command(first_command, &env, &env_var);
		ft_free(&line, &tokens, &first_command);
	}
	return (0);
}
