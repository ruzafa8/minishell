/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:01:17 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/04/29 18:19:03 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	c_to_char;
	size_t			i;

	i = 0;
	c_to_char = (unsigned char) c;
	while (i < n)
	{
		if (*(unsigned char *)s == c_to_char)
			return ((unsigned char *)s);
		s++;
		i++;
	}
	return (0);
}
