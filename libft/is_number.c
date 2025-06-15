#include "libft.h"

int	is_number(char *str)
{
	size_t	i;

	if (str == NULL)
		return (1);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}