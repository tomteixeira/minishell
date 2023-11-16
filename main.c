/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:24:46 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/16 14:53:20 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_signal = 0;

// Function to parse key-value pair from environment string
static int	parse_key_value_pair(const char *env_str, char **key, char **value)
{
	char	*key_value_pair;
	char	*delimiter;

	key_value_pair = ft_strdup(env_str);
	if (!key_value_pair)
		return (0);
	delimiter = ft_strchr(key_value_pair, '=');
	if (!delimiter)
	{
		free(key_value_pair);
		return (0);
	}
	*delimiter = '\0';
	*key = key_value_pair;
	*value = ft_strdup(delimiter + 1);
	return (*value != NULL);
}

// Function to create a new environment variable
t_env_var	*create_env_var(const char *env_str)
{
	t_env_var	*var;
	char		*key;
	char		*value;

	if (!parse_key_value_pair(env_str, &key, &value))
		return (NULL);
	var = malloc(sizeof(t_env_var));
	if (!var)
	{
		free(key);
		free(value);
		return (NULL);
	}
	var->key = key;
	var->value = value;
	var->next = NULL;
	return (var);
}

void	init_env_var(t_env_var **env_var, char **env)
{
	t_env_var	*current_var;
	t_env_var	*previous_var;
	int			i;

	*env_var = NULL;
	if (!env || !*env)
		return ;
	i = 0;
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
	t_minishell	*m;

	(void)argv;
	(void)argc;
	init_variables(&m->env_var, &m->line, &m->tokens, &m->first_command);
	while (42)
	{
		handle_input_signal();
		m->line = read_line();
		if (!m->line)
			exit(0);
		init_env_var(&m->env_var, env);
		if (m->line)
			m->tokens = lexer(m->line);
		if (m->tokens)
			m->first_command = parse_tokens(m->tokens);
		handle_exec_signal();
		if (m->first_command)
			(execute_command(&m, &env));
		ft_free(&m->line, &m->tokens, &m->first_command, &m->env_var);
	}
	return (0);
}
