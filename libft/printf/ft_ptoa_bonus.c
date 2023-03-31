/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:03:20 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/17 13:35:36 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static size_t	ft_num_len(uintptr_t p)
{
	int	len;

	len = 1;
	while (p >= 16)
	{
		len++;
		p /= 16;
	}
	return (len);
}

static void	ft_put_str(uintptr_t p, char *c, size_t pos)
{
	if (p < 16)
		c[pos] = "0123456789abcdef"[p];
	else
	{
		ft_put_str(p / 16, c, pos - 1);
		ft_put_str(p % 16, c, pos);
	}
}

char	*ft_ptoa(void *ptr)
{
	char	*res;
	size_t	size;

	size = ft_num_len((uintptr_t) ptr);
	res = (char *) ft_calloc(size + 3, sizeof(char));
	if (!res)
		return (0);
	ft_put_str((uintptr_t) ptr, res, size + 1);
	res[0] = '0';
	res[1] = 'x';
	return (res);
}
