#include "minishell.h"

//free a los strings pero si ya esta liberao, no lo hace otra vez
void	free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
}