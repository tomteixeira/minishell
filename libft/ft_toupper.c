/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:00:31 by toteixei          #+#    #+#             */
/*   Updated: 2022/10/26 11:11:40 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
#include <unistd.h>

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}
/*
int	main(int argc, char **argv)
{
	int	i = 0;
	while (argv[1][i])
	{
		ft_putchar_fd(ft_toupper(argv[1][i]), 1);
		i++;
	}
	write(1, "\n", 1);
	i = 0;
	while (argv[1][i])
	{
		ft_putchar_fd(toupper(argv[1][i]), 1);
		i++;
	}
	write(1, "\n", 1);
}*/
