#include "minishell.h"

/**
 * This function creates a CD command node.
 * @param path path to send to cd built-in.
 * @returns A pointer to the node or NULL if any allocation problem.
 */
t_command	*create_cd(char *path)
{
	t_command	*res;

	res = (t_command *) ft_calloc(1, sizeof(t_command));
	if (!res)
		return (0);
	res->data = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!res->data)
		return (free(res), (t_command *) 0);
	res->type = CD;
	res->data->cd = (t_cd *) ft_calloc(1, sizeof(t_cd));
	if (!res->data->cd)
		return (free_cd(res->data), free(res), (t_command *) 0);
	res->data->cd->path = ft_strdup(path);
	// TODO: Es necesario esto? Podría llegarme un path NULL?
	if (!res->data->cd->path)
		return (free_cd(res->data), free(res), (t_command *) 0);
	return (res);
}

/**
 * This function makes a free of a CD node.
 * @param data A pointer to the CD node to free.
 */
void	free_cd(t_data	*data)
{
	if (data)
	{
		if (data->cd)
		{
			if (data->cd->path)
				free(data->cd->path);
			free(data->cd);
		}
		free(data);
	}
}