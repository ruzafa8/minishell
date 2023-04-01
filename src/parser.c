/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:37:06 by amorilla          #+#    #+#             */
/*   Updated: 2023/04/01 22:35:21 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	free_tokens(char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
t_command	*parse_command(char *command_str)
{
	char		**tokens;
	t_command	*res;

	tokens = ft_split(command_str, ' ');
	res = 0;
	if (!tokens || !tokens[0])
		return (free(tokens), 0);
	if (ft_strncmp(tokens[0], "cd", 2) == 0)
		res = create_cd(tokens[1]);
	else
		res = create_generic(tokens[0], tokens);
	free_tokens(tokens);
	return (res);
}

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
		aux->args = str;
	}
	return (aux);
}
