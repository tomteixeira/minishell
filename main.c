/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:35:48 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/20 18:35:54 by toteixei         ###   ########.fr       */
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

char	**ft_fill_env(char **env)
{
	char	**n_env;
	int		env_len;
	int		i;

	env_len = 0;
	i = -1;
	while(env[env_len])
		env_len++;
	n_env = malloc((env_len + 1) * sizeof(char *));
	if (!n_env)
		return (NULL);
	while (++i < env_len)
	{
		n_env[i] = ft_strdup(env[i]);
		if (!n_env[i])
			return (ft_free_arrays_i(n_env, i), NULL);
	}
	n_env[env_len] = NULL;
	return (n_env);
}

t_minishell	*init_variables(char **env)
{
	t_minishell *m;

	m = malloc(sizeof(t_minishell));
	if (!m)
		exit(0);
	m->first_command = NULL;
	m->tokens = NULL;
	m->env = ft_fill_env(env);
	if (!m->env)
	{
		free(m);
		exit(0);
	}
	return (m);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*m;
	char		*line;

	(void)argv;
	(void)argc;
	m = init_variables(env);
	init_env_var(&m->env_var, env);
	while (42)
	{
		line = NULL;
		handle_input_signal();
		line = read_line();
		if (!line)
			(ft_free(&m, 1), exit(0));
		if (line)
			m->tokens = lexer(line);
		free(line);
		if (m->tokens)
			m->first_command = parse_tokens(m->tokens);
		handle_exec_signal();
		if (m->first_command)
			(execute_command(&m, &m->env));
		ft_free(&m, 0);
	}
	return (0);
}
