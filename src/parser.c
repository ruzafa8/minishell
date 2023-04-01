/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:37:06 by amorilla          #+#    #+#             */
/*   Updated: 2023/04/01 22:20:34 by amorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_instruction	*parse(char *str)
{
	t_instruction	*aux;
	char			**tokens;

	tokens = ft_split(str, ' ');
	aux = ft_calloc(1, sizeof(t_instruction));
	if (ft_strncmp(tokens[0], "cd", 2) == 0)
	{
		aux->directory = tokens[1];
		aux->type = CD;
		ft_printf("%s AWA %s",tokens[0],tokens[1]);
	}
	else
	{
		aux->type = GENERIC;
		aux->instruction = tokens[0];
		aux->args = tokens;
	}
	return (aux);
}