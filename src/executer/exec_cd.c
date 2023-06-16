/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:38:32 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/06/16 20:41:36 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Change old pwd and new pwd with the one at the parameter 
 * if the "new" parameter is null, then swap oldpwd and pwd
 */
static void	update_pwds(t_shell_data *data, char *new)
{
	char	*oldpwd;
	char	*pwd;

	pwd = get_env_value(data, "PWD");
	set_env_var(data, "OLDPWD", pwd);
	free(pwd);
	if (new[0] == '\0')
	{
		oldpwd = get_env_value(data, "OLDPWD");
		set_env_var(data, "PWD", oldpwd);
		free(oldpwd);
	}
	else
		set_env_var(data, "PWD", new);
}

static int	exec_cd(char *pathaux, t_shell_data *data)
{
	int		res_code;
	char	*new_path;

	res_code = 0;
	if (chdir(pathaux) == -1)
		res_code = 1;
	if (res_code == 0)
	{
		new_path = getcwd(NULL, 0);
		update_pwds(data, new_path);
		free(new_path);
	}
	return (res_code);
}

static int	print_error_cd(char *dir)
{
	return (print_error("cd", dir, strerror(errno), 1));
}

/**
 * Posibles errores del cd:
 * 
 * Too many args,
 * The target might not exist, 
 * the target might not be a directory, 
 * you might not have permission to access the target directory
 */
int	built_in_cd(t_command *command, t_shell_data *data)
{
	int		res_code;
	char	*pathaux;

	res_code = 1;
	if (command->argc == 1
		|| (ft_strncmp(command->argv[1], "--", 3) == 0 && command->argc == 2))
	{
		pathaux = get_env_value(data, "HOME");
		res_code = exec_cd(pathaux, data);
		free(pathaux);
	}
	else if (command->argc == 2 && ft_strncmp(command->argv[1], "..", 3) == 0)
		res_code = exec_cd(command->argv[1], data);
	else if (command->argc == 2 && ft_strncmp(command->argv[1], ".", 2) == 0)
	{
		pathaux = get_env_value(data, "PWD");
		res_code = set_env_var(data, "OLDPWD", pathaux);
		free(pathaux);
	}
	else if (command->argc >= 2)
		res_code = exec_cd(command->argv[1], data);
	if (res_code == 1)
		return (print_error_cd(command->argv[1]));
	return (res_code);
}
