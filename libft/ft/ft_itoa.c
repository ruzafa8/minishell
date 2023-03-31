/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 13:41:54 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/04/24 15:44:20 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_int_len(int n)
{
	size_t	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	ft_process_sign(int *n)
{
	if (*n >= 0)
		return (0);
	*n = -*n;
	return (1);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*res;
	size_t	i;
	int		sign;

	if (n == -2147483648)
		return (ft_strjoin("-21474", "83648"));
	sign = ft_process_sign(&n);
	len = ft_int_len(n) + sign;
	res = (char *) ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (0);
	i = len - 1;
	while (n >= 10)
	{
		res[i--] = (n % 10) + '0';
		n /= 10;
	}
	res[sign] = n + '0';
	if (sign == 1)
		res[0] = '-';
	return (res);
}
