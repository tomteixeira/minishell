/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:43:36 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/16 15:15:37 by tomteixeira      ###   ########.fr       */
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

	while (h)
	{
		cur = h;
		h = h->next;
		ft_free_arrays_i(cur->command->command_args, cur->command->nb_args);
		if (cur->command->in_redirection != NULL)
			free_redirection(cur->command->in_redirection);
		if (cur->command->out_redirection != NULL)
			free_redirection(cur->command->out_redirection);
		if (cur->command)
			free(cur->command);
		free(cur);
	}
}

void	ft_free(char **l, t_tokenlist **token_h,
			t_command_parser **cmd_h, t_env_var **env_var)
{
	if (l)
	{
		free(*l);
		*l = NULL;
	}
	if (token_h)
	{
		free_tokenlist(*token_h);
		*token_h = NULL;
	}
	if (cmd_h)
	{
		free_cmdlist(*cmd_h);
		*cmd_h = NULL;
	}
	if (env_var)
	{
		free_env_var(*env_var);
		*env_var = NULL;
	}
}
