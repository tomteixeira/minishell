/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_fonctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:03:19 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/16 11:34:03 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_len(t_lexer **lexer)
{
	int	i;
	int	count;

	i = (*lexer)->position;
	count = 0;
	while ((*lexer)->input_string[i] != '\0'
		&& ft_word_char((*lexer)->input_string[i]))
	{
		if ((*lexer)->input_string[i] == '\''
			|| (*lexer)->input_string[i] == '\"')
			count += string_len(lexer);
		i++;
		count++;
	}
	return (count);
}

int	string_len(t_lexer **lexer)
{
	int		i;
	int		count;
	char	quote;

	i = (*lexer)->position;
	count = 1;
	quote = (*lexer)->input_string[i++];
	while ((*lexer)->input_string[i] != '\0')
	{
		if ((*lexer)->input_string[i] == quote
			&& (*lexer)->input_string[i - 1] != '\\')
		{
			count++;
			return (count);
		}
		i++;
		count++;
	}
	return (count);
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
