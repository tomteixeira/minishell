/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/16 09:51:08 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_variables(char *str,
	t_env_var *env_var, int *index, int quotes)
{
	char	*new_str;

	if ((quotes == 0 || quotes == 1) && str[*index] == '$'
		&& str[*index + 1] != '\0' && str[*index + 1] != ' '
		&& str[*index + 1] != '\"' && str[*index + 1] != '\''
		&& (*index == 0 || str[*index - 1] != '\\') && str[*index + 1] != '=')
	{
		new_str = expand_variable(str, env_var, *index);
		*index = -1;
	}
	else
		new_str = str;
	return (new_str);
}

static char	*expand_argument(const char *str, t_env_var *env_var)
{
	int		quotes;
	int		i;
	char	*tmp;
	char	*new_tmp;

	i = 0;
	tmp = ft_strdup(str);
	quotes = 0;
	if (!tmp)
		exit_with_error("malloc failed");
	while (tmp[i])
	{
		quotes = handle_quotes(tmp[i], quotes);
		new_tmp = expand_variables(tmp, env_var, &i, quotes);
		if (new_tmp != tmp)
			replace_and_free(&tmp, new_tmp);
		new_tmp = remove_backslashes(tmp, &i);
		if (new_tmp != tmp)
			replace_and_free(&tmp, new_tmp);
		i++;
	}
	new_tmp = apply_quotes_removal(tmp, quotes);
	if (new_tmp != tmp)
		replace_and_free(&tmp, new_tmp);
	return (tmp);
}

void	expand_redirections(t_redirection *redirection, t_env_var *env_var)
{
	char			*expanded_arg;
	t_redirection	*tmp;

	tmp = redirection;
	while (redirection)
	{
		expanded_arg = expand_argument(redirection->file, env_var);
		free(redirection->file);
		redirection->file = ft_strdup(expanded_arg);
		free(expanded_arg);
		redirection = redirection->next;
	}
	redirection = tmp;
}

void	expand_command_args(char **command_args, t_env_var *env_var)
{
	int		i;
	char	*expanded_arg;

	i = 0;
	while (command_args[i] != NULL)
	{
		expanded_arg = expand_argument(command_args[i], env_var);
		free(command_args[i]);
		command_args[i] = ft_strdup(expanded_arg);
		free(expanded_arg);
		i++;
	}
}

void	expand_command_arguments(t_command *cmd, t_env_var *env_var)
{
	expand_redirections(cmd->in_redirection, env_var);
	expand_redirections(cmd->out_redirection, env_var);
	if (cmd->command_args)
		expand_command_args(cmd->command_args, env_var);
}
