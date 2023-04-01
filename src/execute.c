#include "../includes/minishell.h"

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

static int	execaux(t_instruction *instr, char **path, char ** env)
{
	char	*comand_and_path;

	comand_and_path = check_access(instr->instruction, path);
	if (comand_and_path != 0)
	{
		execve(comand_and_path, instr->args, env);
		return (errno);
	}
	return (127);
}

static void	execute_generic(t_instruction *instr, char **path, char **env)
{
	int		pid1;
	int		result_code;

	pid1 = fork();
	if (pid1 < 0)
		exit(pid1);
	if (pid1 == 0)
	{
		result_code = execaux(instr, path, env);
		perror(strerror(result_code));
	}
	waitpid(pid1, 0, 0);
	if (WIFEXITED(result_code))
		exit(WEXITSTATUS(result_code));
}


int	execute(t_instruction *instr, char **path, char **env)
{
	int	status;

	status = 127;
	if (instr->type == CD)
		status = chdir(instr->directory);
	else if (instr->type == GENERIC)
		execute_generic(instr, path, env);
	return (status);
}

