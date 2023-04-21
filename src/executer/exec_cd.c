



#include "minishell.h"


/**
 * change old pwd and new pwd with the one at the parameter 
 * if the "new" parameter is null, then swap oldpwd and pwd
*/
static void	update_pwds(t_shell_data *data, char *new)
{
	char	*aux;

	if(new[0] == '\0') //caso de swap cuando hagas "cd -" o cosas asi
	{
		aux = ft_strdup(get_env_value(data, "OLDPWD"));
		set_env_var(data, "OLDPWD", get_env_value(data, "PWD"));
		set_env_var(data, "PWD", aux);
		free(aux);
	}
	else //caso de cd normal
	{
		set_env_var(data, "OLDPWD", get_env_value(data, "PWD"));
		set_env_var(data, "PWD", new);
	}
}
/*
	Posibles errores del cd:

	Too many args,
	The target might not exist, 
	the target might not be a directory, 
	you might not have permission to access the target directory
*/
int	built_in_cd(t_command *command, t_shell_data *data)
{
	int	res_code;
	char *pathaux;

	if (command->argc == 1 
		|| ft_strncmp(command->argv[1], "--", 3) == 0)
	{
		pathaux = get_env_value(data, "HOME");
		//if (!pathaux)
		//	return (errorcomand(con la info));
		res_code = chdir(pathaux);
		if(res_code == 0) //si el cd va todo perfectisimo
			update_pwds(data, pathaux);
		
		free(pathaux);
	}
	//else if ()
	//{
		
	//}
	else
		res_code = chdir(command->argv[1]);
	return (res_code);
}
