/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:48:35 by toteixei          #+#    #+#             */
/*   Updated: 2022/11/15 10:40:28 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdint.h>

int	ft_print_ptr(uintptr_t ptr)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (ptr < 16)
	{
		ft_putchar_fd(base[ptr], 1);
		count++;
	}
	if (ptr >= 16)
	{
		count += ft_print_ptr(ptr / 16);
		count += ft_print_ptr(ptr % 16);
	}
	return (count);
}

int	ft_treat_ptr(unsigned long long ptr)
{
	int	count;

	count = 0;
	if (ptr == 0)
		count += write(1, "(nil)", 5);
	else
	{
		count += write(1, "0x", 2);
		count += ft_print_ptr(ptr);
	}
	return (count);
}
