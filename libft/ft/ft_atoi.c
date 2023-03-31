/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:18:02 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/02/18 19:17:53 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(const char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ' );
}

static int	ft_check_len(const char *str)
{
	int	len;
	int	sign;

	sign = *str == '-';
	while (*str == '+' || *str == '-' || *str == '0')
		str++;
	len = ft_strlen(str);
	if (sign == 1 && len > 10)
		return (0);
	else if (sign == 0 && len > 10)
		return (-1);
	return (1);
}

static int	validate_overflow(int sign, int res)
{
	if (sign == 1 && res < 0)
		return (-1);
	else if (sign == -1 && res > 0)
		return (0);
	return (res);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	len_overflow;

	res = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	len_overflow = ft_check_len(str);
	if (len_overflow <= 0)
		return (len_overflow);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		res *= 10;
		res += *str - '0';
		str++;
	}
	res *= sign;
	return (validate_overflow(sign, res));
}
