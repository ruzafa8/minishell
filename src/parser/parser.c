#include "minishell.h"

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
t_command	*parse(char *command_str)
{
	char		**tokens;
	t_command	*res;

	if (!command_str || ft_strncmp(command_str, "", 1) == 0)
		return (0);
	tokens = ft_split(command_str, ' ');
	res = 0;
	if (!tokens || !tokens[0])
		return (free(tokens), (t_command *)0);
	if (ft_strncmp(tokens[0], "cd", 2) == 0)
		res = create_cd(tokens[1]);
	else
		res = create_generic(tokens[0], tokens);
	ft_printf("ASASA: %s\n", res->data->generic->full_command[1]);
	free_tokens(tokens);
	return (res);
}
