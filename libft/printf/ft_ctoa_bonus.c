/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:33:49 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/17 13:35:01 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

char	*ft_ctoa(char c)
{
	char	*res;

	res = ft_calloc(2, sizeof(char));
	if (!res)
		return (0);
	res[0] = c;
	return (res);
}
