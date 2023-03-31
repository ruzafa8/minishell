/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:14:52 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/04/24 17:16:47 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = (char *) malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!res)
		return (0);
	i = -1;
	while (++i < s1_len)
		res[i] = s1[i];
	i = -1;
	while (++i < s2_len)
		res[s1_len + i] = s2[i];
	res[s1_len + s2_len] = 0;
	return (res);
}
