/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:50:55 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/28 18:51:42 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "../ft/libft.h"

int			ft_printf(char const *format, ...);
int			ft_print_format(char *format, va_list args);
int			ft_printptr(void *ptr);

#endif
