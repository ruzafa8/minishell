/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basetoa_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:57:54 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/21 14:19:39 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static unsigned int	ft_num_len(unsigned int base_len, unsigned int number)
{
	unsigned int	res;

	res = 1;
	while (number >= base_len)
	{
		res++;
		number /= base_len;
	}
	return (res);
}

static void	ft_recursive_print(unsigned int number, char *base,
		char *res, unsigned int position)
{
	unsigned int	base_len;

	base_len = (unsigned int) ft_strlen(base);
	if (number < base_len)
		res[position] = base[number];
	else
	{
		ft_recursive_print(number / base_len, base, res, position - 1);
		ft_recursive_print(number % base_len, base, res, position);
	}
}

char	*ft_to_ascii(unsigned int number, char *base, t_format *f, size_t size)
{
	char	*res;

	res = (char *) ft_calloc(size + 1, sizeof(char));
	if (!res)
		return (0);
	ft_memset(res, '0', size - 1);
	if (number != 0 || !f->precision_present || f->precision != 0)
		ft_recursive_print(number, base, res, size - 1);
	return (res);
}

char	*ft_basetoa(unsigned int number, char *base, t_format *f)
{
	unsigned int	len;
	char			*res;

	len = ft_num_len((unsigned int) ft_strlen(base), number);
	if (f->hashtag && f->width >= len + 2 && number != 0 && f->zero
		&& !f->precision_present)
	{
		res = ft_to_ascii(number, base, f, f->width);
		if (!res)
			return (0);
		res[1] = f->specifier;
		return (res);
	}
	if (!f->hashtag && f->width >= len && number != 0 && f->zero
		&& !f->precision_present)
		return (ft_to_ascii(number, base, f, f->width));
	if (f->precision_present && f->precision >= len)
		res = ft_to_ascii(number, base, f, f->precision);
	else
		res = ft_to_ascii(number, base, f, len);
	if (!res)
		return (0);
	if (f->hashtag && number != 0)
		res = ft_add_begin('0', ft_add_begin(f->specifier, res));
	return (res);
}
