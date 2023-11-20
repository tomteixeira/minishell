/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:24:46 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/19 16:53:23 by hebernar         ###   ########.fr       */
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

t_minishell	*init_variables(void)
{
	t_minishell *m;

	m = malloc(sizeof(t_minishell));
	if (!m)
		exit(0);
	m->env_var = NULL;
	m->first_command = NULL;
	m->tokens = NULL;
	return (m);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*m;
	char		*line;

	(void)argv;
	(void)argc;
	while (42)
	{
		line = NULL;
		handle_input_signal();
		line = read_line();
		if (!line)
			exit(0);
		m = init_variables();
		init_env_var(&m->env_var, env);
		if (line)
			m->tokens = lexer(line);
		free(line);
		if (m->tokens)
			m->first_command = parse_tokens(m->tokens);
		handle_exec_signal();
		if (m->first_command)
			(execute_command(&m, &env));
		ft_free(&m);
	}
	return (0);
}
