/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:20:25 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/28 18:23:28 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	gnl_strjoin(char **s1, char *s2, size_t s2_len)
{
	char	*res;
	size_t	i;
	size_t	s1_len;

	if (s2_len == 0)
		return ;
	s1_len = ft_strlen(*s1);
	res = (char *) ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!res)
	{
		free(*s1);
		*s1 = 0;
		return ;
	}
	i = -1;
	while (++i < s1_len)
		res[i] = (*s1)[i];
	i = -1;
	while (++i < s2_len)
		res[s1_len + i] = s2[i];
	free(*s1);
	*s1 = res;
}
