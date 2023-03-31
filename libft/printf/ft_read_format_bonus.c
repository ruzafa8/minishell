/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_format_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:00:05 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/21 16:06:01 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static char	*ft_read_str(char *c, t_format *f)
{
	char	*res;
	char	*aux;

	if (!c)
		res = ft_strdup("(null)");
	else
		res = ft_strdup(c);
	if (f->precision_present)
	{
		aux = res;
		res = (char *) ft_substr(res, 0, f->precision);
		free(aux);
	}
	return (res);
}

static int	ft_read_data(char **str, va_list args, t_format *f)
{	
	f->specifier = **str;
	if (**str == 'c')
		f->data = ft_ctoa((char) va_arg(args, int));
	else if (**str == 's')
		f->data = ft_read_str(va_arg(args, char *), f);
	else if (**str == 'p')
		f->data = ft_ptoa(va_arg(args, void *));
	else if (**str == 'd' || **str == 'i')
		f->data = ft_itoa_sized(va_arg(args, int), f);
	else if (**str == 'u')
		f->data = ft_basetoa(va_arg(args, unsigned int), "0123456789", f);
	else if (**str == 'x')
		f->data = ft_basetoa(va_arg(args, unsigned int), "0123456789abcdef", f);
	else if (**str == 'X')
		f->data = ft_basetoa(va_arg(args, unsigned int), "0123456789ABCDEF", f);
	else if (**str == '%')
		f->data = ft_ctoa('%');
	if (!f->data)
	{
		free(f);
		return (0);
	}
	(*str)++;
	return (1);
}

static size_t	ft_simple_atoi(char **str)
{
	int	res;

	res = 0;
	while (ft_isdigit(**str))
	{
		res *= 10;
		res += **str - '0';
		(*str)++;
	}
	return (res);
}

static void	ft_read_flags(char **str, t_format *format)
{
	while (**str)
	{
		if (**str == '-')
			format->minus = 1;
		else if (**str == '0')
			format->zero = 1;
		else if (**str == '#')
			format->hashtag = 1;
		else if (**str == ' ')
			format->space = 1;
		else if (**str == '+')
			format->plus = 1;
		else
			return ;
		(*str)++;
	}
}

t_format	*ft_read_format(char **str, va_list args)
{
	t_format	*format;

	format = (t_format *) ft_calloc(1, sizeof(t_format));
	if (!format)
		return (0);
	ft_read_flags(str, format);
	if (ft_isdigit(**str))
		format->width = ft_simple_atoi(str);
	if (**str == '.')
	{
		(*str)++;
		format->precision_present = 1;
		format->precision = ft_simple_atoi(str);
	}
	if (!ft_read_data(str, args, format))
		return (0);
	if (format->specifier == 'c')
		format->size = 1;
	else
		format->size = ft_strlen(format->data);
	return (format);
}
