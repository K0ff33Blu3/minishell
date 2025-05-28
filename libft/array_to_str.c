/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_to_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:40:43 by miricci           #+#    #+#             */
/*   Updated: 2025/05/28 09:54:22 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*array_to_str(char **arr, char *sep, int size)
{
	int	tot_len;
	int	word_len;
	int	i;
	char	*str;

	word_len = 0;
	i = 0;
	while (i < size)
		word_len += ft_strlen(arr[i++]);
	tot_len = word_len + ((size - 1) * ft_strlen(sep));
	str = (char *)ft_calloc((tot_len + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < size - 1)
	{
		ft_strlcat(str, arr[i], ft_strlen(str) + ft_strlen(arr[i]) + 1);
		ft_strlcat(str, sep, ft_strlen(str) + ft_strlen(sep) + 1);
		i++;
	}
	ft_strlcat(str, arr[i], ft_strlen(str) + ft_strlen(arr[i]) + 1);
	str[tot_len] = 0;
	return (str);
}

// int	main()
// {
// 	char	*array[4] = {
// 		"ciao", "$$", "\"come\"ciao", "stai"
// 	};
// 	char *str = array_to_str(array, " ", 4);
	
// 	printf("%s\n", str);
// 	free(str);
// 	return (0);
// }