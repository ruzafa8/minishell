



#include "minishell.h"

int	built_in_export(t_command *command, t_shell_data *data)
{
	//QUE PASA SI PONGO MUCHAS SEGUIDAS??
	//EL ENV DEL EXPORT hay que hacerlo si o si
	//COÑAZO GRANDE, SI PONES UNA 'ñ' EN EL NOMBRE DE UNA VARIABLE DEBERIA DE FALLAR ¿¿¿¿¿o si pones '_'???? ((ft_isprint))
	
	set_env_var(t_shell_data *data, char *key, char *value)
}