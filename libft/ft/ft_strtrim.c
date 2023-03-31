/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:25:25 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/04/24 17:05:09 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_belong(char const s, char const *set)
{
	while (*set)
	{
		if (*set == s)
			return (42);
		set++;
	}
	return (0);
}

static size_t	ft_count_to_delete(char const *s, char const *set, size_t len)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (i < len && ft_belong(s[i], set))
	{
		count++;
		i++;
	}
	i = len - 1;
	while (i >= 0 && ft_belong(s[i], set) && count < len)
	{
		count++;
		i--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	len;
	size_t	new_len;
	size_t	i;

	if (!s1 || !set)
		return (0);
	len = ft_strlen(s1);
	new_len = len - ft_count_to_delete(s1, set, len) + 1;
	res = (char *) malloc(new_len * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (i < len && ft_belong(s1[i], set))
		i++;
	ft_strlcpy(res, s1 + i, new_len);
	return (res);
}
