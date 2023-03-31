/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:08:15 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/04/24 17:39:49 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_c;
	unsigned char	*s2_c;

	if (n == 0)
		return (0);
	s1_c = (unsigned char *) s1;
	s2_c = (unsigned char *) s2;
	while (*s1_c == *s2_c && --n)
	{
		s1_c++;
		s2_c++;
	}
	return (*s1_c - *s2_c);
}
