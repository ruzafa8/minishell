#include "minishell.h"

int	built_in_cd(t_command *command, t_shell_data *data)
{
	int	res_code;
	char *pathaux;

	if (command->argc == 1 
		|| ft_strncmp(command->argv[1], "--", 3) == 0)
	{
		pathaux = get_env_value(data, "HOME");
	//	if (!pathaux)
	//		return (errorcomand(con la info));
		res_code = chdir(pathaux);
		//EL SET ENV VAR SE RECOYE
		set_env_var(data, "y", "y");
		//update_pwds() cambiar el pwd y el OLDpwd en el env a los nuevos
	}
	else
		res_code = chdir(command->argv[1]);
	return (res_code);
}