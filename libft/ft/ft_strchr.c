/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:41:47 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/04/24 17:47:17 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	while (*s && (unsigned char)(*s) != (char)c)
		s++;
	if ((unsigned char)(*s) == (char)c)
		return ((char *)s);
	return (0);
}
