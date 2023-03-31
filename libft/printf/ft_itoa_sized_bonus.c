/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_sized_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:11:01 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/21 13:51:02 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static char	*ft_zero_case(t_format *f)
{
	if (f->zero && f->width > 0)
	{
		f->zero = 0;
		f->space = 1;
	}
	return (ft_strdup(""));
}

char	*append_at_begining(char c, size_t num, char *str, size_t len_str)
{
	char	*res;

	res = (char *) ft_calloc(num, sizeof(char));
	if (!res)
		return (0);
	ft_memset(res, c, num - len_str - 1);
	ft_strlcat(res, str, num);
	return (res);
}

char	*ft_itoa_precision(int number, t_format *f)
{
	char	*res;
	char	*aux;
	size_t	len;

	if (number == 0 && f->precision_present && f->precision == 0)
		return (ft_zero_case(f));
	res = ft_itoa(number);
	if (!res)
		return (0);
	len = ft_strlen(res);
	aux = res;
	if (number < 0 && f->precision_present && f->precision > len - 1)
	{
		res = append_at_begining('0', f->precision + 2, aux + 1, len - 1);
		free(aux);
		if (res)
			res[0] = '-';
	}
	else if (f->precision_present && f->precision > len)
	{
		res = append_at_begining('0', f->precision + 1, aux, len);
		free(aux);
	}
	return (res);
}

static char	*ft_concat(char c, char *n_c, size_t size, char *to_delete)
{
	char	*res;

	res = (char *) ft_calloc(size, sizeof(char));
	if (res)
	{
		ft_memset(res, '0', size - ft_strlen(n_c) - 1);
		res[0] = c;
		ft_strlcat(res, n_c, size);
	}
	free(to_delete);
	return (res);
}

char	*ft_itoa_sized(int n, t_format *f)
{
	char	*n_c;

	n_c = ft_itoa_precision(n, f);
	if (!n_c)
		return (0);
	if (n < 0 && f->zero && !f->precision_present && f->width > ft_strlen(n_c))
		return (ft_concat('-', n_c + 1, f->width + 1, n_c));
	if (n >= 0 && f->plus && f->zero && !f->precision_present
		&& f->width > ft_strlen(n_c))
		return (ft_concat('+', n_c, f->width + 1, n_c));
	if (n >= 0 && f->space && f->zero && !f->precision_present
		&& f->width > ft_strlen(n_c))
		return (ft_concat(' ', n_c, f->width + 1, n_c));
	if (f->plus && n >= 0)
		n_c = ft_add_begin('+', n_c);
	else if (f->space && n >= 0)
		n_c = ft_add_begin(' ', n_c);
	return (n_c);
}
