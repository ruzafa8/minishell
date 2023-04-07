/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:47:58 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/30 12:54:48 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include "ft/libft.h"

/**
  * Lee una línea del fd proporcionado hasta llegar al salto de línea.
  * @param fd El file descriptor del que se va a leer.
  * @returns El string reservado con la línea incluyendo el saltn de línea
  * o NULL en caso de error.
  * En caso de que hayamos llegado al final del archivo, devolvemos
  * el string sin salto de línea.
  */
char	*ft_get_next_line(int fd);

/**
  * Imprime la línea con el formato especificado:
  * Los formatos implementados son los siguientes: cspdiuxX%
  * Los flags implementados son los siguentes: -0.# + y el ancho mínimo.
  * (Sí, uno de ellos es el espacio)
  * @param format el string con un formato
  * @param valores Por cada %formato, pasar su valor en una variable (variádicas)
  * @returns el nº de caracteres impreso.
  */
int		ft_printf(char const *format, ...);

#endif
