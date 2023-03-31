/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:58:43 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/28 18:20:39 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		len;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	res = (char *) malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	ft_memcpy(res, s1, len + 1);
	return (res);
}
