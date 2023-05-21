

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

static void expand_var(char **line, t_shell_data* data)
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

static void	read_heredoc(int fd, char *value, t_shell_data *data)
{
	char	*line;
	size_t	value_len;

	value_len = ft_strlen(value);
	while (1)
	{
		line = readline(" :: heredocker >> ");
		if (!line)
			break ;
		expand_var(&line, data);
		if (ft_strncmp(line, value, value_len) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

t_pars_err	pars_create_heredoc(t_list	*commands, char *value, t_shell_data *data)
{
	t_command		*command;
	static size_t	next_heredoc_code = 0;
	char			*filename;
	char			*tmp;

	command = (t_command *) ft_lstlast(commands)->content;
	tmp = ft_itoa(next_heredoc_code++);
	if (!tmp)
		return (PARS_MALLOC_ERROR);
	filename = ft_strjoin("/tmp/.minishel_heredoc_", tmp);
	free(tmp);
	if (!filename)
		return (PARS_MALLOC_ERROR);
	read_heredoc(open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666),
		value, data);
	command->fd_in = open(filename, O_RDONLY, 0666);
	return (PARS_NO_ERROR);
}
