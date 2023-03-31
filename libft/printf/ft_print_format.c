/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:24:24 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/17 13:51:13 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchr(char c)
{
	return (write(1, &c, 1));
}

static int	ft_putstr(char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}

static int	ft_printbase(unsigned int number, char *base)
{
	unsigned int	base_len;
	int				res;

	base_len = ft_strlen(base);
	if (number < base_len)
		return (write(1, base + number, 1));
	else
	{
		res = ft_printbase(number / base_len, base);
		if (res == -1)
			return (-1);
		if (ft_printbase(number % base_len, base) == -1)
			return (-1);
		return (res + 1);
	}
}

static int	ft_print_int(int number)
{
	char	*str_num;
	int		res;

	str_num = ft_itoa(number);
	if (!str_num)
		return (-1);
	res = ft_putstr(str_num);
	free(str_num);
	return (res);
}

int	ft_print_format(char *str, va_list args)
{
	if (*str == 'c')
		return (ft_putchr((char) va_arg(args, int)));
	else if (*str == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (*str == 'p')
		return (ft_printptr(va_arg(args, void *)));
	else if (*str == 'd' || *str == 'i')
		return (ft_print_int(va_arg(args, int)));
	else if (*str == 'u')
		return (ft_printbase(va_arg(args, unsigned int), "0123456789"));
	else if (*str == 'x')
		return (ft_printbase(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (*str == 'X')
		return (ft_printbase(va_arg(args, unsigned int), "0123456789ABCDEF"));
	else if (*str == '%')
		return (ft_putchr('%'));
	else
		return (0);
}
