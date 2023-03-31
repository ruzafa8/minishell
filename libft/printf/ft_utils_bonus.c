/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:02:10 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/18 17:06:25 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_add_begin(char c, char *str)
{
	size_t	size;
	char	*aux;

	if (!str)
		return (0);
	aux = str;
	size = ft_strlen(str);
	str = (char *) ft_calloc(size + 2, sizeof(char));
	if (!str)
	{
		free(aux);
		return (0);
	}
	str[0] = c;
	ft_strlcat(str, aux, size + 2);
	free(aux);
	return (str);
}
