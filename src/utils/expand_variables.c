

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

static char	*concat_me(char *line, int line_count, char *var_value, int var_name_len)
{
	char	*result;
	char	*str1;
	char	*str2;

	str1 = ft_substr(line, 0, line_count - 1);
	str2 = ft_substr(line, line_count + var_name_len, -1);
	result = ft_strjoin(str1, var_value);
	free(str1);
	str1 = ft_strjoin(result, str2);
	free(result);
	free(str2);
	return (str1);
}

void	expand_variables(char **line, t_shell_data* data)
{
	int		var_name_len;
	int		line_count;
	char	*var_value;
	char	*aux;

	line_count = 0;
	while (*(*line + line_count))
	{
		if (*(*line + line_count) == '$')
		{
			line_count++;
			var_value = get_var(data, (*line) + line_count, &var_name_len);
			if (var_name_len == 0)
				continue ;
			if (!var_value)
				var_value = ft_strdup("");
			if (!var_value)
				return ;
			aux = concat_me(*line, line_count, var_value, var_name_len);
			free(*line);
			*line = aux;
			free(var_value);
		}
		else
			line_count++;
	}
}
