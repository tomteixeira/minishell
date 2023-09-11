/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_fonctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:03:19 by toteixei          #+#    #+#             */
/*   Updated: 2023/08/28 15:06:26 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		command_len(t_lexer **lexer)
{
	int	i;
	int	count;
	
	i = (*lexer)->position;
	count = 0;
	while ((*lexer)->input_string[i] != '\0' && ft_isalpha((*lexer)->input_string[i]))
	{
		i++;
		count++;
	}
	return (count);
}

int		string_len(t_lexer **lexer)
{
	int		i;
	int		count;
	char	quote;
	
	i = (*lexer)->position;
	count = 1;
	quote = (*lexer)->input_string[i++];
	while ((*lexer)->input_string[i] != '\0')
	{
		if ((*lexer)->input_string[i] == quote && (*lexer)->input_string[i - 1] != '\\')
		{
			count++;
			return (count);
		}
		i++;
		count++;
	}
	return (count);
}

int	option_len(t_lexer **lexer)
{
	int	i;
	int	count;
	
	i = (*lexer)->position + 1;
	count = 1;
	while ((*lexer)->input_string[i] != '\0' && ft_isalpha((*lexer)->input_string[i]))
	{
		i++;
		count++;
	}
	return (count);
}