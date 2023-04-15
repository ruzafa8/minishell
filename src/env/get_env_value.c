#include "minishell.h"

static char	*free_args(char **arg)
{
	if (!arg)
		return (0);
	if (arg[0] != 0)
		free(arg[0]);
	if (arg[1] != 0)
		free(arg[1]);
	free(arg);
	return (0);
}
//tiene que coger el env de t_shell_data
char	*get_env_value(char **env, char *key)
{
	char	**arg;
	char	*res;
	size_t	key_len;

	key_len = ft_strlen(key);
	while (env)
	{
		arg = ft_split(*env, '=');
		if (!arg || !arg[0] || !arg[1])
			return (free_args(arg));
		if (ft_strncmp(arg[0], key, key_len) == 0)
		{
			res = ft_strdup(arg[1]);
			free_args(arg);
			return (res);
		}
		else
			free_args(arg);
		env++;
	}
	return (0);
}