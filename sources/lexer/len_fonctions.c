/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_fonctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:03:19 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/16 17:37:17 by tomteixeira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	string_len(const char *cmdline, int *i)
{
	int		count;
	char	quote;

	count = 1;
	quote = cmdline[*i];
	i++;
	while (cmdline[*i] != '\0')
	{
		if (cmdline[*i] == quote)
		{
			count++;
			return (count);
		}
		printf("s %c\n", cmdline[*i]);
		i++;
		count++;
	}
	return (count);
}

int	command_len(t_lexer **lexer)
{
	t_command_len	p;

	p.i = (*lexer)->position - 1;
	p.count = 0;
	while ((*lexer)->input_string[++p.i] != '\0'
		&& ft_word_char((*lexer)->input_string[p.i]))
	{
		if ((*lexer)->input_string[p.i] == '\''
			|| (*lexer)->input_string[p.i] == '\"')
		{
			p.quote = (*lexer)->input_string[p.i++];
			p.count++;
			while ((*lexer)->input_string[p.i]
				&& (*lexer)->input_string[p.i] != p.quote)
			{
				p.i++;
				p.count++;
			}
			if ((*lexer)->input_string[p.i] == '\0')
				return (ft_putstr_fd("bash: unclosed quote\n", 2), -1);
		}
		p.count++;
	}
	return (p.count);
}

int	ft_string_char(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	if ((c >= 32 && c < 127) || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

int	ft_word_char(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (0);
	if (c > 32 && c < 127)
		return (1);
	else
		return (0);
}
