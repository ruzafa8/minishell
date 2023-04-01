#include "minishell.h"

void	loop_shell(char **path, char **env)
{
	char			*line;
	t_instruction	*instr;
	int status;

	status = 1;
	while (status)
	{
		ft_printf("> ");
		line = ft_get_next_line(1);//TODO: cuidao con los leaks
		line = ft_strtrim(line, "\n");
		instr = parse(line);
		status = execute(instr, path, env);
		free(line);
		free(instr);
	}
}