#include "minishell.h"

/**
 * Makes free of a char ** upto a size
 * @param args the char ** to free.
 * @param size the number of char * to free.
 */
static void	free_duplicate(char **args, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(args[i]);
	free(args);
}

/**
 * Function that duplicates a char **
 * @param args the char ** to duplicate.
 * @returns a copy of args param.
 */
static char	**duplicate_command(char **args)
{
	char	**copy;
	size_t	num_args;
	size_t	i;

	num_args = 0;
	i = 0;
	while (args[num_args])
		num_args++;
	copy = (char **) ft_calloc(num_args + 1, sizeof(char *));
	if (!copy)
		return (0);
	while (args[i])
	{
		copy[i] = ft_strdup(args[i]);
		if (!copy[i])
		{
			free_duplicate(copy, i);
			return (0);
		}
		i++;
	}
	return (copy);
}

/**
 * This function creates a GENERIC command node.
 * @param command command to send to execve the found command.
 * @param full_command command with parameters to send to execve
 * the found command.
 * @returns A pointer to the node or NULL if any allocation problem.
 */
t_command_old	*create_generic(char *command, char **full_command)
{
	t_command_old	*res;

	res = (t_command_old *) ft_calloc(1, sizeof(t_command_old));
	if (!res)
		return (0);
	res->data = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!res->data)
		return (free(res), (t_command_old *) 0);
	res->type = GENERIC;
	res->data->generic = (t_generic *) ft_calloc(1, sizeof(t_generic));
	if (!res->data->generic)
		return (free(res), (t_command_old *) 0);
	res->data->generic->command = ft_strdup(command);
	// TODO: Es necesario esto? Podría llegarme un command NULL?
	if (!res->data->generic->command)
		return (free(res), (t_command_old *) 0);
	res->data->generic->full_command = duplicate_command(full_command);
	// TODO: Es necesario esto? Podría llegarme un full_command NULL?
	if (!res->data->generic->full_command)
		return (free(res), (t_command_old *) 0);
	return (res);
}
