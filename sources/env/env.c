/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:49:09 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/04 13:57:49 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append_env(t_env **head, char *line)
{
	t_env	*last_node;
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->var = line;
	node->next = NULL;		//gerer les problemes de memoires
	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	last_node = *head;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = node;
	return ;
}

t_env	*fill_env(char **env)
{
	t_env 	*first_node;
	int		i;

	first_node = NULL;
	i = 0;
	while (env[i])
	{
		append_env(&first_node, env[i]);
		i++;
	}
	return (first_node);
}