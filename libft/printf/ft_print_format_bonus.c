/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:24:24 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/21 16:23:38 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	delete(t_format *f)
{
	free(f->data);
	free(f);
}

static char	get_space_char(t_format *f)
{
	if (f->zero && !f->precision_present && f->specifier != '%')
		return ('0');
	return (' ');
}

static int	print_space(t_format *f, size_t times)
{
	size_t	i;
	char	c;

	c = get_space_char(f);
	i = 0;
	while (i < times)
	{
		if (write(1, &c, 1) == -1)
			return (-1);
		i++;
	}
	return (times);
}

static int	ft_error(t_format *f)
{
	delete(f);
	return (-1);
}

int	ft_print_format(char **str, va_list args)
{
	t_format	*format;
	size_t		ret;

	format = ft_read_format(str, args);
	if (!format)
		return (-1);
	ret = format->size;
	if (format->width > format->size && !format->minus)
	{
		if (print_space(format, format->width - format->size) == -1)
			return (ft_error(format));
		ret = format->width;
	}
	if (write(1, format->data, format->size) == -1)
		return (ft_error(format));
	if (format->width > format->size && format->minus)
	{
		if (print_space(format, format->width - format->size) == -1)
			return (ft_error(format));
		ret = format->width;
	}
	delete(format);
	return ((int) ret);
}
