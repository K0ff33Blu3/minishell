/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:03:04 by miricci           #+#    #+#             */
/*   Updated: 2025/05/28 14:13:21 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var_in_quotes(char *quote)
{
	int		len;
	int		start;
	char	*pos;
	char	*value;
	char	*var;

	pos = ft_strchr(quote, '$') + 1;
	start = pos - quote;
	len = word_len(quote, start);
	var = ft_substr(quote, start, len);
	if (!var)
		return (NULL);
	value = getenv(var);
	if (value)
		return (free(var), value);
	return (var);
}

char	*expand_var(char *var)
{
	char	*name_var;
	char	*value;

	name_var = var + 1;
	value = ft_strdup(getenv(name_var));
	if (value)
		return (value);
	return (var);
}

char	*expanded_quote(char *quote)
{
	char	*start_str;
	char	*partial_str;
	char	*final_str;
	int	start_quote;
	char	*end_str;

	start_quote = ft_strchr(quote, '$') - quote;
	start_str = ft_substr(quote, 0, start_quote);
	partial_str = ft_strjoin(start_str, expand_var_in_quotes(quote));
	end_str = ft_strchr(quote, '$') + word_len(quote, start_quote);
	final_str = ft_strjoin(partial_str, end_str);
	free(start_str);
	free(partial_str);
	return (final_str);
}

char	**expand_env_var(char **token)
{
	int		i;
	char	**expanded_token;

	i = 0;
	expanded_token = malloc(sizeof(char *) * (array_size((void **)token) + 1));
	if (!expanded_token)
		return (NULL);
	while (token[i])
	{
		if (ft_strchr(token[i], '$'))
		{
			if (*token[i] == '\'')
				expanded_token[i] = ft_strdup(token[i]);
			else if (*token[i] == '\"')
				expanded_token[i] = expanded_quote(token[i]);
			else
				expanded_token[i] = expand_var(token[i]);
		}
		else
			expanded_token[i] = ft_strdup(token[i]);
		i++;
	}
	expanded_token[i] = NULL;
	return (ft_free((void **)token, -1), expanded_token);
}

char	**remove_quotes(char **str)
{
	int	i;
	char	quote;
	char	**no_quotes;

	no_quotes = malloc(sizeof(char *) * (array_size((void **)str) + 1));
	if (!no_quotes)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (*str[i] == '\'' || *str[i] == '\"')
		{
			quote = *str[i];
			no_quotes[i] = ft_strtrim(str[i], &quote);
		}
		else
			no_quotes[i] = ft_strdup(str[i]);
		i++;
	}
	no_quotes[i] = NULL;
	return (ft_free((void **)str, -1), no_quotes);	
}

char	**get_data_token(char *str)
{
	char	**partial_token;
	char	**exp_token;
	char	**re_token;
	char	**no_quotes_token;

	partial_token = tokenize(str);
	if (!partial_token)
		return (NULL);
	exp_token = expand_env_var(partial_token);
	if (!exp_token)
		return (NULL);
	re_token = re_tokenize(exp_token, array_size((void **)exp_token));
	ft_free((void **)exp_token, -1);
	no_quotes_token = remove_quotes(re_token);
	if (!no_quotes_token)
		return (NULL);
	return (no_quotes_token);
}

t_cmdline	*data_parsing(char *cmd_str)
{
	t_cmdline	*data;
	
	data = (t_cmdline *)malloc(sizeof(t_cmdline));
	if (!data)
		return (NULL);
	data->token = get_data_token(cmd_str);
	//handle logical operators
	//handle redirections
	
	return (data);
}

int main(void)
{
	char	**result;
	char	*str = "echo \"Ciao $USER ciao\" | grep Ciao && echo \"Fine\" > out.txt";
	int i = 0;

	result = get_data_token(str);
	while (result[i])
	{
		printf("%s\n", result[i]);
		i++;
	}
	ft_free((void **)result, -1);
	return (0);	
}

// t_list	**pipe_parsing(char *cmd_line)
// {
// 	t_cmdline	*data;
// 	t_list		**head;
// 	t_list		*node;
// 	char	**splitted_cmd_line;
// 	int	i;

// 	i = 0;
// 	head = malloc(sizeof(t_list));
// 	if (!head)
// 		return (NULL);
// 	*head = NULL;
// 	splitted_cmd_line = ft_split(cmd_line, '|');
// 	if (!splitted_cmd_line)
// 		return (NULL);
// 	while (splitted_cmd_line[i])
// 	{
// 		data = data_parsing(splitted_cmd_line[i]);
// 		node = ft_lstnew((void *)data);
// 		if (!node)
// 			return (NULL);
// 		ft_lstadd_back(head, node);
// 		i++;		
// 	}
// 	ft_free((void **)splitted_cmd_line, -1);
// 	return (head);
// }
