/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:51:05 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/18 17:13:36 by amorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_env(char *str)
{
	int		idx_sep;
	int		i;
	char	**splitted;

	idx_sep = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			idx_sep = i;
			break ;
		}
		i++;
	}
	if (idx_sep == 0)
		return (0);
	splitted = (char **)ft_calloc(3, sizeof(char *));
	if (!splitted)
		return (0);
	splitted[0] = ft_substr(str, 0, idx_sep);
	splitted[1] = ft_substr(str, idx_sep + 1, ft_strlen(str));
	return (splitted);
}
