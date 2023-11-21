/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/21 16:13:52 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_var(t_env_var *env_var)
{
	t_env_var	*cur;

	while (env_var)
	{
		cur = env_var;
		env_var = env_var->next;
		if (cur->key)
			free(cur->key);
		if (cur->value)
			free(cur->value);
		free(cur);
	}
}

void	free_tokenlist(t_tokenlist *h)
{
	t_tokenlist	*cur;

	while (h)
	{
		cur = h;
		h = h->next;
		if (cur->token->value)
			free(cur->token->value);
		if (cur->token)
			free(cur->token);
		free(cur);
	}
}

void	free_redirection(t_redirection *h)
{
	t_redirection	*cur;

	while (h)
	{
		cur = h;
		h = h->next;
		if (cur->file)
			free(cur->file);
		free(cur);
	}
}

void	free_cmdlist(t_command_parser *h)
{
	t_command_parser	*cur;

	while (h && h->previous)
		h = h->previous;
	while (h)
	{
		cur = h;
		h = h->next;
		if (cur->command)
			ft_free_arrays_i(cur->command->cargs, cur->command->nb_args);
		if (cur->command->in_redirection != NULL)
			free_redirection(cur->command->in_redirection);
		if (cur->command->out_redirection != NULL)
			free_redirection(cur->command->out_redirection);
		if (cur->command)
			free(cur->command);
		free(cur);
	}
}

void	ft_free(t_minishell **m, int exit_flag)
{
	if ((*m)->tokens)
	{
		free_tokenlist((*m)->tokens);
		(*m)->tokens = NULL;
	}
	if ((*m)->f_c)
	{
		free_cmdlist((*m)->f_c);
		(*m)->f_c = NULL;
	}
	if ((*m)->env_var && exit_flag == 2)
	{
		free_env_var((*m)->env_var);
		(*m)->env_var = NULL;
	}
	if (exit_flag > 0)
	{
		ft_free_arrays_i((*m)->env, -1);
		free(*m);
	}
}
