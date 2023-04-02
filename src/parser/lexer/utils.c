#include "minishell.h"

/**
 * Returns a copy of the string until a char is found
*/
char	*get_until(char *str, char c)
{
	char	*res;
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	res = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(res, str, i + 1);
	return (res);
}
/**
 * Returns if the first word of the string is a given string
*/
int	is_command(char *str, char *word)
{
	size_t	i;

	if (!str || !word)
		return (0);
	i = 0;
	while (str[i] && word[i] && str[i] == word[i])
		i++;
	if (word[i] == '\0' && (str[i] == ' ' || str[i] == '\0'))
		return (1);
	return (0);
}
