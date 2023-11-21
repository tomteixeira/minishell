/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:35:48 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/21 18:42:30 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_signal = 0;

t_minishell	*init_variables(char **env)
{
	t_minishell	*m;

	m = malloc(sizeof(t_minishell));
	if (!m)
		exit(0);
	m->f_c = NULL;
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
	rl_outstream = stderr;
	m = init_variables(env);
	init_env_var(&m->env_var, env);
	while (42)
	{
		line = NULL;
		handle_input_signal();
		line = read_line();
		if (!line)
			(ft_free(&m, 2), exit(0));
		if (line)
			m->tokens = lexer(line);
		free(line);
		if (m->tokens)
			m->f_c = parse_tokens(m->tokens);
		handle_exec_signal();
		if (m->f_c)
			(execute_command(&m, &m->env));
		ft_free(&m, 0);
	}
	return (0);
}
