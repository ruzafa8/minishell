/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:48:46 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/04/25 11:29:51 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_c;
	unsigned char	*s2_c;

	if (n == 0)
		return (0);
	s1_c = (unsigned char *) s1;
	s2_c = (unsigned char *) s2;
	while (*s1_c && *s2_c && *s1_c == *s2_c && --n)
	{
		s1_c++;
		s2_c++;
	}
	return (*s1_c - *s2_c);
}
