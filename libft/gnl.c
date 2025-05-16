/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:40:41 by miricci           #+#    #+#             */
/*   Updated: 2025/04/03 11:30:08 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*write_buffer(char *current_buffer, char *src)
{
	char	*new_buffer;

	if (!current_buffer)
	{
		new_buffer = ft_strdup(src);
		if (!new_buffer)
			return (free(src), NULL);
		return (new_buffer);
	}
	new_buffer = ft_strjoin(current_buffer, src);
	if (!new_buffer)
		return (free(src), current_buffer);
	free(current_buffer);
	return (new_buffer);
}

static char	*get_buffer(int fd, char *buffer)
{
	int		bytes_read;
	char	*tmp;

	tmp = (char *)malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	*tmp = '\0';
	while (!ft_strchr(tmp, '\n'))
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == 0)
			return (free(tmp), buffer);
		if (bytes_read < 0)
			return (free(tmp), free(buffer), NULL);
		tmp[bytes_read] = 0;
		buffer = write_buffer(buffer, tmp);
	}
	free(tmp);
	return (buffer);
}

static char	*get_next_buffer(char *current_buffer, char *new_line, int len)
{
	char	*new_buffer;

	new_buffer = ft_substr(current_buffer, len, ft_strlen(new_line));
	if (!*new_buffer)
	{
		free(new_buffer);
		new_buffer = NULL;
	}
	free(current_buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char		*buffer[1024];
	char			*line;
	char			*new_line;
	int				len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = get_buffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	new_line = ft_strchr(buffer[fd], '\n');
	if (new_line)
	{
		new_line++;
		len = ft_strlen(buffer[fd]) - ft_strlen(new_line);
		line = ft_substr(buffer[fd], 0, len);
		buffer[fd] = get_next_buffer(buffer[fd], new_line, len);
	}
	else
	{
		line = ft_strdup(buffer[fd]);
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
