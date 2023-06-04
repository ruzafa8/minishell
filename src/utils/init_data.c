#include "minishell.h"

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	init_env(t_shell_data *aux, char **env)
{
	int	i = 0;

	aux->env = ft_calloc(env_size(env) + 1, sizeof(aux->env));
	if (!aux->env)
		return (0); //error en el initenv
	while (env[i])
	{
		aux->env[i] = ft_strdup(env[i]);
		if (!aux->env[i])
			return (0);//liberar cosas?????? error tambien en el initenv
		i++;
	}
	return (1);
}

int	init_export_env(t_shell_data *aux, char **env)
{
	int	i = 0;

	aux->exportenv = ft_calloc(env_size(env) + 1, sizeof(aux->env));
	if (!aux->exportenv)
		return (0); //error en el initenv
	while (env[i])
	{
		aux->exportenv[i] = ft_strdup(env[i]);
		if (!aux->exportenv[i])
			return (0);//liberar cosas?????? error tambien en el initenv
		i++;
	}
	return (1);
}

t_shell_data	*init_shell_data(char **env)
{
	t_shell_data	*aux;

	aux = (t_shell_data *)ft_calloc(1, sizeof(t_shell_data));
	init_env(aux, env);
	init_export_env(aux, env);
	//if(!init_env(aux, env)){
		//printerror
		//exit_shell(NULL, EXIT_FAILURE);
	//}

	//iniciar resto de cosas que hay en shelldata
	return (aux);
}