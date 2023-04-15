#include "minishell.h"

int	built_in_cd(t_command_old *istr, t_shell_data *sh_data)
{
	int	res_code;
	char *pathaux;

	if (ft_strncmp(istr->data->cd->path, "", 1) == 0
		|| ft_strncmp(istr->data->cd->path, "--", 3) == 0)
	{
		pathaux = get_env_value(sh_data->env, "HOME");
	//	if (!pathaux)
	//		return (errorcomand(con la info));
		res_code = chdir(pathaux);
		//update_pwds() cambiar el pwd y el OLDpwd en el env a los nuevos
	}
	else
		res_code = chdir(istr->data->cd->path);
	return (res_code);
}