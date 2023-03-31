/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:55:52 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/17 13:52:16 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_error(va_list args)
{
	va_end(args);
	return (-1);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		num_print;
	int		printed;

	va_start(args, format);
	num_print = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			printed = ft_print_format((char *) format++, args);
			if (printed == -1)
				return (ft_error(args));
			num_print += printed;
		}
		else
		{
			if (write(1, format++, 1) == -1)
				return (ft_error(args));
			num_print++;
		}
	}
	va_end(args);
	return (num_print);
}
