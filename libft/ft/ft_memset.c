/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:56:17 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/04/22 14:29:55 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int ch, size_t count)
{
	unsigned char	*dest_as_char;

	dest_as_char = (unsigned char *) dest;
	while (count--)
		*dest_as_char++ = ch;
	return (dest);
}
