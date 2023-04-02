#include "minishell.h"

int	built_in_cd(t_command *istr)
{
	if (ft_strncmp(istr->data->cd->path, "", 1) == 0)
	{
		chdir("/");
	}
	else
		chdir(istr->data->cd->path);
	return (1);
}