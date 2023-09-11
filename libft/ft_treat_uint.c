/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:15:15 by toteixei          #+#    #+#             */
/*   Updated: 2022/11/12 17:46:11 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_treat_uint(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb < 10)
	{
		ft_putchar_fd((nb + 48), 1);
		count++;
	}
	if (nb >= 10)
	{
		count += ft_treat_uint(nb / 10);
		count += ft_treat_uint(nb % 10);
	}
	return (count);
}
/*
int	main(int argc, char **argv)
{
	int	i;

	i = ft_treat_uint(1652431);
	ft_printf("\n");
	ft_printf("%d", i);
	return (0);
}*/
