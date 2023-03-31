/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:15:37 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/04/22 14:38:29 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_as_char;
	unsigned char	*src_as_char;

	dst_as_char = (unsigned char *) dst;
	src_as_char = (unsigned char *) src;
	if (!dst && !src)
		return (0);
	while (n--)
		dst_as_char[n] = src_as_char[n];
	return (dst);
}
