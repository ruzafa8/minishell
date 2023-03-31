/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:01:50 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/08 17:37:28 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_num_words(char *s, char c)
{
	int	num;

	num = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s == c)
		{
			num++;
			while (*s && *s == c)
				s++;
			if (!*s)
				return (num);
		}
		else
			s++;
	}
	return (num + 1);
}

static size_t	ft_len_next_word(char *s, char c, size_t *start)
{
	size_t	len;

	len = 0;
	while (s[*start] && s[*start] == c)
		(*start)++;
	while (s[*start + len] && s[*start + len] != c)
		len++;
	return (len);
}

static char	**ft_delete(char **res, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (0);
}

static char	**ft_compute(char *s, char c, size_t num_words)
{
	size_t	word;
	char	**res;
	size_t	len_word;
	size_t	s_index;

	res = (char **) ft_calloc(num_words + 1, sizeof(char *));
	if (!res)
		return (0);
	word = 0;
	s_index = 0;
	while (word < num_words)
	{
		len_word = ft_len_next_word(s, c, &s_index);
		if (len_word)
		{
			res[word] = ft_substr(s, s_index, len_word);
			s_index += len_word;
			if (!res[word])
				return (ft_delete(res, word));
		}
		word++;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	*s_trim;
	char	**res;
	char	*set;

	if (!s)
		return (0);
	set = ft_calloc(2, sizeof(char));
	if (!set)
		return (0);
	set[0] = c;
	s_trim = ft_strtrim(s, set);
	free(set);
	if (!s_trim)
		return (0);
	if (ft_strlen(s_trim) == 0)
	{
		free(s_trim);
		return ((char **) ft_calloc(1, sizeof(char *)));
	}
	res = ft_compute(s_trim, c, ft_num_words(s_trim, c));
	free(s_trim);
	return (res);
}
