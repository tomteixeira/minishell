/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:21:14 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/17 15:31:59 by tomteixeira      ###   ########.fr       */
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
	(*command)->command_args = args;
	return (args);
}

char	**fill_args(t_token *token, t_command **command)
{
	char	**args;
	int		j;

	if (!(*command)->command_args)
		return (first_arg(token, command));
	args = malloc(((*command)->nb_args + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	j = 0;
	while (j < (*command)->nb_args - 1)
	{
		args[j] = ft_strdup((*command)->command_args[j]);
		if (!args[j])
			return (ft_free_arrays_i(args, j), NULL);
		j++;
	}
	args[j] = ft_strdup(token->value);
	if (!args[j])
		return (ft_free_arrays_i(args, j), NULL);
	args[j + 1] = NULL;
	ft_free_arrays_i((*command)->command_args, (*command)->nb_args);
	(*command)->nb_args++;
	return (args);
}

t_command	*fill_command(t_tokenlist **token)
{
	t_command	*command;

	command = init_command();
	if (!command)
		return (NULL);
	while ((*token) && (*token)->token->type != T_PIP)
	{
		if ((*token)->token->type == T_WORD)
		{
			command->command_args = fill_args((*token)->token, &command);
			if (!command->command_args)
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
	return (command);
}

t_command_parser	*parse_tokens(t_tokenlist *token)
{
	t_command_parser	*first_command;

	if (token == NULL)
		return (NULL);
	first_command = NULL;
	append(&first_command, &token, 0);
	if (!first_command)
		return (free_cmdlist(first_command), NULL);
	while (token != NULL)
	{
		if (token->token->type == T_PIP && token->next)
		{
			token = token->next;
			append(&first_command, &token, 1);
			if (token == NULL)
				break ;
		}
	}
	if (token != NULL)
		return (free_cmdlist(first_command), NULL);
	return (first_command);
}

void	print_parser(t_command_parser *head)
{
	t_command_parser	*buffer;
	int					i;

	buffer = head;
	while (head)
	{
		i = 0;
		while (i < head->command->nb_args - 1)
		{
			printf("Argument %d : %s\n", i, head->command->command_args[i]);
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
}