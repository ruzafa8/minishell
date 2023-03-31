/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:33:19 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/17 13:53:08 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_recursive_printptr(uintptr_t ptr)
{
	int	res;

	if (ptr < 16)
		return (write(1, &"0123456789abcdef"[ptr], 1));
	res = ft_recursive_printptr(ptr / 16);
	if (res == -1)
		return (-1);
	if (ft_recursive_printptr(ptr % 16) == -1)
		return (-1);
	return (res + 1);
}

int	ft_printptr(void *ptr)
{
	int	res;

	if (write(1, "0x", 2) == -1)
		return (-1);
	res = ft_recursive_printptr((uintptr_t) ptr);
	if (res == -1)
		return (-1);
	return (res + 2);
}
