/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:23:21 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/20 15:02:22 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_no_args(char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		write(1, "declare -x ", 11);
		j = -1;
		while (env[i][++j])
		{
			if (env[i][j] == '=')
			{
				write(1, &env[i][j], 1);
				write(1, "\"", 1);
				while (env[i][++j])
					write(1, &env[i][j], 1);
				write(1, "\"", 1);
				break ;
			}
			write(1, &env[i][j], 1);
		}
		write(1, "\n", 1);
	}
}

int	check_var(char *var, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_strlenchr(env[i], '=')) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**unset_var(char *var, char **e)
{
	t_unset	p;

	p.env_count = 0;
	while (e[p.env_count])
		p.env_count++;
	p.new_env = malloc((p.env_count) * sizeof(char *));
	if (!p.new_env)
		return (NULL);
	p.i = 0;
	p.j = 0;
	while (p.i < p.env_count - 1)
	{
		if (e[p.j] && ft_strncmp(var, e[p.j], ft_strlenchr(e[p.j], '=')) != 0)
		{
			p.new_env[p.i] = ft_strdup(e[p.j]);
			if (!p.new_env[p.i])
				return (ft_free_arrays_i(p.new_env, p.i), NULL);
			p.i++;
			p.j++;
		}
		else
			p.j++;
	}
	p.new_env[p.i] = NULL;
	return (p.new_env);
}

#include "../../includes/minishell.h"

// Existing code...

// Function to remove a variable from the linked list
void remove_env_var(t_env_var **env_var, char *var) {
	t_env_var *temp = *env_var;
	t_env_var *prev = NULL;

	while (temp) {
		if (strcmp(temp->key, var) == 0) {
			if (prev == NULL) {
				*env_var = temp->next;
			} else {
				prev->next = temp->next;
			}
			free(temp->key);
			free(temp->value);
			free(temp);
			return;
		}
		prev = temp;
		temp = temp->next;
	}
}

int	unset(char **args, char ***env, t_minishell	**minishell)
{
	int		i;
	char	**n_env;

	i = 1;
	if (!args[i])
		return (EXIT_SUCCESS);
	while (args[i])
	{
		if (check_var(args[i], *env) == 1)
		{
			n_env = unset_var(args[i], *env);
			ft_free_arrays_i(*env, -1);
			*env = n_env;
			if (!*env)
				return (EXIT_FAILURE);
			remove_env_var(&(*minishell)->env_var, args[i]);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
