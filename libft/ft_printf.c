/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:22:06 by toteixei          #+#    #+#             */
/*   Updated: 2022/11/12 17:44:09 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_treat_percent(va_list *arg, const char format)
{
	int	count;

	count = 0;
	if (format == '%')
	{
		ft_putchar_fd('%', 1);
		count++;
	}
	else if (format == 'i' || format == 'd')
		count += ft_treat_int(va_arg(*arg, int));
	else if (format == 'c')
		count += ft_treat_char(va_arg(*arg, int));
	else if (format == 's')
		count += ft_treat_string(va_arg(*arg, char *));
	else if (format == 'x' || format == 'X')
		count += ft_treat_hexa(va_arg(*arg, int), format);
	else if (format == 'p')
		count += ft_treat_ptr(va_arg(*arg, unsigned long long));
	else if (format == 'u')
		count += ft_treat_uint(va_arg(*arg, unsigned int));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		count;
	int		i;

	count = 0;
	i = 0;
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_treat_percent(&arg, format[i]);
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			count++;
		}
		i++;
	}
	va_end(arg);
	return (count);
}
