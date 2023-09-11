/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:47:43 by toteixei          #+#    #+#             */
/*   Updated: 2022/11/12 19:59:30 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_treat_hexa2(unsigned int nbr)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789ABCDEF";
	if (nbr < 16)
	{
		ft_putchar_fd(base[nbr], 1);
		count++;
	}
	if (nbr >= 16)
	{
		count += ft_treat_hexa2(nbr / 16);
		count += ft_treat_hexa2(nbr % 16);
	}
	return (count);
}

int	ft_treat_hexa(unsigned int nbr, const char format)
{
	int		count;
	char	*base;

	if (format == 'X')
		return (ft_treat_hexa2(nbr));
	count = 0;
	base = "0123456789abcdef";
	if (nbr < 16)
	{
		ft_putchar_fd(base[nbr], 1);
		count++;
	}
	if (nbr >= 16)
	{
		count += ft_treat_hexa(nbr / 16, format);
		count += ft_treat_hexa(nbr % 16, format);
	}
	return (count);
}
/*
int	main(int argc, char **argv)
{
	int	i;

	i = ft_treat_hexa(123, 'X');
	printf("\n");
	printf("%d", i);
}*/
