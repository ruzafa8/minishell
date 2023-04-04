/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:33:33 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/04/27 14:15:19 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*res;
	size_t			mult;

	mult = count * size;
	if (count != 0 && mult / count != size)
		return (0);
	res = (unsigned char *) malloc(mult);
	if (!res)
		return (0);
	ft_bzero(res, mult);
	return (res);
}
