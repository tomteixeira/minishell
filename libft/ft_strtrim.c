/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:00:11 by toteixei          #+#    #+#             */
/*   Updated: 2023/02/21 16:25:45 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	total_len(char const *str, char const *set)
{
	int	len;
	int	i;
	int	final_size;

	i = 0;
	len = ft_strlen(str);
	final_size = len;
	while (is_charset(str[i], set))
	{
		final_size--;
		i++;
	}
	if (final_size == 0)
		return (final_size);
	len -= 1;
	while (len >= 0 && is_charset(str[len], set))
	{
		final_size--;
		len--;
	}
	return (final_size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*str;

	i = 0;
	j = 0;
	k = 0;
	if (!s1 || !set)
		return (NULL);
	len = total_len(s1, set);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (is_charset(s1[i], set))
		i++;
	while (k < len)
	{
		str[j++] = s1[i++];
		k++;
	}
	str[j] = 0;
	return (str);
}
/*
int	main(int argc, char **argv)
{
	char *str;
	str = ft_strtrim(argv[1], argv[2]);
	printf("%s", str);
	return (0);
}*/
