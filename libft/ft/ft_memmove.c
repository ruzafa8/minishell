/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:19:37 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/04/22 14:39:03 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	i;
	unsigned char	*dst_as_char;
	unsigned char	*src_as_char;

	if (!dst && !src)
		return (0);
	dst_as_char = (unsigned char *) dst;
	src_as_char = (unsigned char *) src;
	if (dst > src)
		while (len--)
			dst_as_char[len] = src_as_char[len];
	else
	{
		i = 0;
		while (i < len)
		{
			dst_as_char[i] = src_as_char[i];
			i++;
		}
	}
	return (dst);
}
