#include "minishell.h"

int	built_in_cd(t_command *istr, char **env)
{
	int	res_code;

	if (ft_strncmp(istr->data->cd->path, "", 1) == 0)
	{
		res_code = chdir(get_env_value(env, "HOME"));
	}
	else
		res_code = chdir(istr->data->cd->path);
	return (res_code);
}