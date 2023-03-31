/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:50:55 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/02/19 16:44:57 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h>
# include "../ft/libft.h"

typedef struct s_format
{
	char	*data;
	char	specifier;
	size_t	size;
	size_t	width;
	size_t	precision;
	int		precision_present;
	int		minus;
	int		zero;
	int		hashtag;
	int		space;
	int		plus;
}			t_format;

int			ft_printf(char const *format, ...);
int			ft_print_format(char **format, va_list args);
t_format	*ft_read_format(char **format, va_list args);
char		*ft_ctoa(char c);
char		*ft_ptoa(void *ptr);
char		*ft_basetoa(unsigned int number, char *base, t_format *f);
char		*ft_itoa_sized(int number, t_format *f);
char		*ft_add_begin(char c, char *str);

#endif
