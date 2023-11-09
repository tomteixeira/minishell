/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:13:24 by toteixei          #+#    #+#             */
/*   Updated: 2023/03/22 11:17:24 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	check_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	else
		return (0);
}

static int	ft_splitlen(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && !check_sep(str[i], c))
		i++;
	return (i);
}

static int	ft_count_words(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && check_sep(str[i], c))
			i++;
		if (str[i])
			count++;
		while (str[i] && !check_sep(str[i], c))
			i++;
	}
	return (count);
}

static char	*ft_fill_word(const char *str, char c)
{
	int		i;
	int		len;
	char	*tab;

	i = 0;
	len = ft_splitlen(str, c);
	tab = malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (i < len)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		nbw;
	char	**res;

	i = 0;
	nbw = ft_count_words(s, c);
	res = malloc((nbw + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (*s)
	{
		while (*s && check_sep(*s, c))
			s++;
		if (*s)
		{
			res[i] = ft_fill_word(s, c);
			if (!res[i])
				return (ft_free_arrays_i(res, i), NULL);
			i++;
		}
		while (*s && !check_sep(*s, c))
			s++;
	}
	res[i] = 0;
	return (res);
}
/*
int	main(int argc, char **argv)
{
	int	i;
	char	**tab;

	i = 0;
	tab = ft_split(argv[1], 32);
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
}*/
