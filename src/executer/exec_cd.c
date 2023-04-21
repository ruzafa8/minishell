



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
	char *dotdotcd;

	if (command->argc == 1 
		|| (ft_strncmp(command->argv[1], "--", 3) == 0 && command->argc == 2)) //ir a home
	{
		pathaux = get_env_value(data, "HOME");
		//if (!pathaux)
		//	return (errorcomand(con la info));
		res_code = chdir(pathaux);
		if(res_code == 0) //si el cd va todo perfectisimo
			update_pwds(data, pathaux);
		free(pathaux);
	}
	else if (command->argc == 2 && ft_strncmp(command->argv[1], "..", 3) == 0) //volver patras
	{
		dotdotcd = get_env_value(data, "PWD");
		res_code = chdir(command->argv[1]);
		if(res_code == 0) //si el cd va todo perfectisimo
		{
			pathaux = getcwd(NULL, 0);//getcwd genera leaks?????
			update_pwds(data, pathaux);
			free(pathaux);
		}
		free(dotdotcd);

	}
	else if (command->argc == 2 && ft_strncmp(command->argv[1], ".", 2) == 0)
	{
		res_code = set_env_var(data, "OLDPWD", get_env_value(data, "PWD"));
	}
	else if (command->argc == 2) //cd clasic
	{
		res_code = chdir(command->argv[1]);
		if(res_code == 0) //si el cd va todo perfectisimo
			update_pwds(data, command->argv[1]);
	}
	else //cambiar porque es basura los errores por ahora
		res_code = 1;


	return (res_code);
}
