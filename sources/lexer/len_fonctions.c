/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_fonctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:03:19 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/18 10:28:59 by tomteixeira      ###   ########.fr       */
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
	int		i;
	int		count;
	char	quote;
	
	i = (*lexer)->position - 1;
	count = 0;
	while ((*lexer)->input_string[++i] != '\0'
		&& ft_word_char((*lexer)->input_string[i]))
	{
		if ((*lexer)->input_string[i] == '\''
			|| (*lexer)->input_string[i] == '\"')
		{
			quote = (*lexer)->input_string[i++];
			count++;
			while ((*lexer)->input_string[i] && (*lexer)->input_string[i] != quote)
			{
				i++;
				count++;
			}
			if ((*lexer)->input_string[i] == '\0')
				return (count);
		}
		count++;
	}
	return (count);
}

int	ft_string_char(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (0);
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
