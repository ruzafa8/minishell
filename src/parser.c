/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:37:06 by amorilla          #+#    #+#             */
/*   Updated: 2023/03/31 21:38:07 by amorilla         ###   ########.fr       */
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
	}
	else
	{
		aux->type = GENERIC;
		aux->instruction = tokens[0];
		aux->args = 
	}
	return (aux);
}