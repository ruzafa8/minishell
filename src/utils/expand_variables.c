/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:43:53 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/06/04 17:58:30 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var(t_shell_data *data, char *line, int *var_len)
{
	char	*var_name;
	char	*var_value;

	*var_len = 0;
	while (*(line + *var_len) && ft_isalnum(*(line + *var_len)))
		(*var_len)++;
	if (*var_len == 0)
		return (NULL);
	var_name = ft_substr(line, 0, *var_len);
	var_value = get_env_value(data, var_name);
	free(var_name);
	return (var_value);
}

static void	concat_me(char **line, int count, char *var_value, int var_name_len)
{
	char	*aux;
	char	*str1;
	char	*str2;
	char	*result;

	str1 = ft_substr(*line, 0, count);
	str2 = ft_substr(*line, count + var_name_len + 1, -1);
	aux = ft_strjoin(str1, var_value);
	result = ft_strjoin(aux, str2);
	free(str1);
	free(str2);
	free(aux);
	free(*line);
	*line = result;
}

void	expand_variables(char **line, t_shell_data* data, int expand_quotes)
{
	int		var_name_len;
	int		line_count;
	char	*var_value;
	int		quote_found;

	line_count = 0;
	quote_found = 0;
	while (*(*line + line_count))
	{
		if (*(*line + line_count) == '\'')
			quote_found = !quote_found;
		if (*(*line + line_count) == '$' && (!quote_found || expand_quotes))
		{
			var_value = get_var(data, (*line) + line_count + 1, &var_name_len);
			if (var_name_len == 0)
				continue ;
			if (!var_value)
				var_value = ft_strdup("");
			if (!var_value)
				return ;
			concat_me(line, line_count, var_value, var_name_len);
			line_count += ft_strlen(var_value);
			free(var_value);
		}
		else
			line_count++;
	}
}
