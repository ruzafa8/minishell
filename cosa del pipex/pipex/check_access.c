/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:05:19 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/02/25 16:25:57 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*px_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = (char *) ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!res)
		return (0);
	i = -1;
	while (++i < s1_len)
		res[i] = s1[i];
	i = -1;
	while (++i < s2_len)
		res[s1_len + i] = s2[i];
	return (res);
}

char	*px_check_access(char *command, char **path)
{
	char	*full_command;
	int		i;

	if (access(command, X_OK) == 0)
		return (command);
	i = 0;
	while (path[i])
	{
		full_command = px_strjoin(path[i], command);
		if (!full_command)
			return (0);
		if (access(full_command, X_OK) == 0)
			return (full_command);
		free(full_command);
		i++;
	}
	return (0);
}
