#include "minishell.h"

char	*check_access(char *command, char **path)
{
	char	*command_and_path;
	int		i;

	if (access(command, X_OK) == 0)
		return (command);
	i = 0;
	while (path[i])
	{
		command_and_path = ft_strjoin(path[i], command);
		if (!command_and_path)
			return (0);
		if (access(command_and_path, X_OK) == 0)
			return (command_and_path);
		free(command_and_path);
		i++;
	}
	return (0);
}

static int	execaux(t_command *instr, t_shell_data *data)
{
	char	*comand_and_path;
	char	**path;

	path = get_path(data->env);
	if (!path)
		return (1);
	comand_and_path = check_access(instr->argv[0], path);
	if (comand_and_path != 0)
	{
		execve(comand_and_path, instr->argv, data->env);
		return (errno);
	}
	return (127);
}

static int	execute_generic(t_command *instr, t_shell_data *data)
{
	int		pid1;
	int		result_code;

	pid1 = fork();
	result_code = 0; // Código de error genérico.
	if (pid1 < 0)
		return (pid1);
	if (pid1 == 0)
	{
		result_code = execaux(instr, data);
		exit(result_code);
	}
	waitpid(pid1, 0, 0);
	/*
	if (WIFEXITED(result_code))
	{
		ft_printf("%d", WEXITSTATUS(result_code));
		exit(WEXITSTATUS(result_code));
	}*/
	return (result_code);
}
/*
static int debug_env(t_shell_data *data)
{
	ft_printf("OLDPWD = %s\n",get_env_value(data,"OLDPWD"));
	ft_printf("PWD = %s\n",get_env_value(data,"PWD"));
	return (0);
}
*/

int	execute(t_list *instr, t_shell_data *data)
{
	int	status;
	t_command *command;

	//setear señales del modo no interactivo el control c y el control barra CORTAN LA EJECUCION
	command = (t_command *) instr->content;
	if (command->fd_in > 0)
		dup2(command->fd_in, STDIN_FILENO);
	if (command->fd_out > 0)
		dup2(command->fd_out, STDOUT_FILENO);
	close_pipes(data, instr);
	if (ft_strncmp(command->argv[0], "cd", 3) == 0)
		status = built_in_cd(command, data);
	else if (ft_strncmp(command->argv[0], "env", 4) == 0)
		status = built_in_env(command, data);//debug_env(data);
	else if (ft_strncmp(command->argv[0], "export", 7) == 0)
		status = built_in_export(command, data);
	else if (ft_strncmp(command->argv[0], "unset", 6) == 0)
		status = built_in_unset(command, data);
	else if (ft_strncmp(command->argv[0], "exit", 5) == 0)
		exit(0);
	else if (ft_strncmp(command->argv[0], "echo", 5) == 0)
		status = built_in_echo(command);
	else
		status = execute_generic(command, data);
	if (command->fd_out > 0)
		close(command->fd_out);
	if (instr->next)
		close(((t_command *)instr->next->content)->fd_in);
	if (command->fd_in > 0)
		dup2(data->dup_stdin, STDIN_FILENO);
	if (command->fd_out > 0)
		dup2(data->dup_stdout, STDOUT_FILENO);
	return (status);
}

int	execute_pipex(t_shell_data *data)
{
	int		status;
	int		last_pid;
	int		last_status;
	t_list	*commands;

	commands = data->commands;
	while (commands)
	{
		last_pid = fork();
		if (last_pid < 0)
			return (last_pid);
		if (last_pid == 0)
			exit (execute(commands, data));
		commands = commands->next;
	}
	commands = data->commands;
	close_pipes(data, 0);
	commands = data->commands;
	while (commands)
	{
		if (last_pid == waitpid(-1, &status, 0))
			last_status = status;
		commands = commands->next;
	}
	return (last_status);
}
