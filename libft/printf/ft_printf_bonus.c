/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:55:52 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/21 16:23:27 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_return(va_list args, int res)
{
	va_end(args);
	return (res);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		num_print;
	int		printed;
	char	**str;

	va_start(args, format);
	str = (char **) &format;
	num_print = 0;
	while (**str)
	{
		if (**str == '%')
		{
			(*str)++;
			printed = ft_print_format(str, args);
			if (printed == -1)
				return (ft_return(args, -1));
			num_print += printed;
			continue ;
		}
		if (write(1, (*str)++, 1) == -1)
			return (ft_return(args, -1));
		num_print++;
	}
	return (ft_return(args, num_print));
}
