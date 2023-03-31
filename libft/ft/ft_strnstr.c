/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:10:25 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/04/25 11:52:46 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!ft_strlen(needle))
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] && needle[j]
			&& haystack[i + j] == needle[j] && i + j < len)
			j++;
		if (!needle[j])
			return ((char *)(haystack + i));
		i++;
	}
	return (0);
}
