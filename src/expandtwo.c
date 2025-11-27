/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandtwo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmondo <elmondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:32:48 by elmondo           #+#    #+#             */
/*   Updated: 2025/11/27 17:32:50 by elmondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*name_var(char *str)
{
	char	*name;
	int		name_len;

	name_len = 0;
	if (str[name_len] == '?')
		return (ft_strdup("?"));
	while (ft_isalnum(str[name_len]) || str[name_len] == '_')
		name_len++;
	name = (char *)malloc(sizeof(char) * (name_len + 1));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, name_len + 1);
	return (name);
}

char	**expand_env_var(t_list **env_list, char **token, int status)
{
	int		i;
	char	**expanded_token;

	i = 0;
	expanded_token = malloc(sizeof(char *) * (array_size((void **)token) + 1));
	if (!expanded_token)
		return (NULL);
	while (token[i])
	{
		expanded_token[i] = expand_str_recursive(env_list, token[i], status);
		i++;
	}
	expanded_token[i] = NULL;
	return (ft_free((void **)token, -1), expanded_token);
}
