/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:21:14 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/21 15:26:04 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void				print_parser(t_command_parser *head);

char	**first_arg(t_token *token, t_command **command)
{
	char	**args;

	args = malloc(2 * sizeof(char *));
	if (!args)
		return (NULL);
	args[0] = ft_strdup(token->value);
	if (!args[0])
		return (ft_free_arrays_i(args, 0), NULL);
	args[1] = NULL;
	(*command)->nb_args = 2;
	(*command)->cargs = args;
	return (args);
}

char	**fill_args(t_token *token, t_command **command)
{
	char	**args;
	int		j;

	if (!(*command)->cargs)
		return (first_arg(token, command));
	args = malloc(((*command)->nb_args + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	j = 0;
	while (j < (*command)->nb_args - 1)
	{
		args[j] = ft_strdup((*command)->cargs[j]);
		if (!args[j])
			return (ft_free_arrays_i(args, j), NULL);
		j++;
	}
	args[j] = ft_strdup(token->value);
	if (!args[j])
		return (ft_free_arrays_i(args, j), NULL);
	args[j + 1] = NULL;
	ft_free_arrays_i((*command)->cargs, (*command)->nb_args);
	(*command)->nb_args++;
	return (args);
}

t_command	*fill_command(t_tokenlist **token)
{
	t_command	*command;
	t_tokenlist	**tmp;

	tmp = token;
	command = init_command();
	if (!command)
		return (NULL);
	while ((*token) && (*token)->token->type != T_PIP)
	{
		if ((*token)->token->type == T_WORD)
		{
			command->cargs = fill_args((*token)->token, &command);
			if (!command->cargs)
				return (free(command), NULL);
		}
		if ((*token)->token->type == T_RED)
		{
			if (fill_redirection(token, &command) == 0)
				return (NULL);
			(*token) = (*token)->next;
		}
		*token = (*token)->next;
	}
	token = tmp;
	return (command);
}

t_command_parser	*parse_tokens(t_tokenlist *token)
{
	t_command_parser	*f_c;

	if (token == NULL)
		return (NULL);
	f_c = NULL;
	append(&f_c, &token, 0);
	if (!f_c)
		return (free_cmdlist(f_c), NULL);
	while (token != NULL)
	{
		if (token->token->type == T_PIP && token->next)
		{
			token = token->next;
			append(&f_c, &token, 1);
			if (token == NULL)
				break ;
		}
	}
	if (token != NULL)
		return (free_cmdlist(f_c), NULL);
	return (f_c);
}

/*void	print_parser(t_command_parser *head)
{
	t_command_parser*buffer;
	int i;

	buffer = head;
	while (head)
	{
		i = 0;
		while (i < head->command->nb_args - 1)
		{
			printf("Argument %d : %s\n", i, head->command->cargs[i]);
			i++;
		}
		if (head->command->in_redirection != NULL)
		{
			while (head->command->in_redirection)
			{
				printf("Infile redirection : %s\n",
					head->command->in_redirection->file);
				head->command->in_redirection = head->command->in_redirection->next;
			}
		}
		if (head->command->out_redirection != NULL)
		{
			while (head->command->out_redirection)
			{
				printf("Outfile redirection : %s\n",
					head->command->out_redirection->file);
				head->command->out_redirection = head->command->out_redirection->next;
			}
		}
		if (head->command->pipe_after == 1)
			printf(" | pipe after\n");
		printf("\n");
		head = head->next;
	}
	head = buffer;
}*/
