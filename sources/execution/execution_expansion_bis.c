/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_expansion_bis.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/09 12:29:08 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_quotes(const char *str, int quote_type)
{
	int		count;
	char	quote_char;

	count = 0;
	if (quote_type == 1)
		quote_char = '\"';
	else
		quote_char = '\'';
	while (*str)
	{
		if (*str == quote_char)
			count++;
		str++;
	}
	return (count);
}

char	*allocate_without_quotes(const char *str, int quotes_nb)
{
	size_t	length;
	char	*result;

	length = ft_strlen(str) - quotes_nb;
	result = (char *)malloc(sizeof(char) * (length + 1));
	if (!result)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	return (result);
}

char	*remove_quotes_from_str(const char *str,
	char quote_char, char *result)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != quote_char)
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*remove_quotes(const char *str, int flag)
{
	int		quotes_nb;
	char	*result;
	char	quote_char;

	if (flag == 1)
		quote_char = '\"';
	else
		quote_char = '\'';
	quotes_nb = count_quotes(str, flag);
	result = allocate_without_quotes(str, quotes_nb);
	return (remove_quotes_from_str(str, quote_char, result));
}

char	*apply_quotes_removal(char *str, int quotes)
{
	char	*new_str;

	if (quotes)
	{
		new_str = remove_quotes(str, quotes);
		return (new_str);
	}
	return (str);
}
