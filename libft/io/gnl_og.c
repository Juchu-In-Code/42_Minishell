/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:29:28 by jgalizio          #+#    #+#             */
/*   Updated: 2024/10/01 17:29:28 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*extract_line(char *buffer)
{
	char	*leftover;
	ssize_t	i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == 0 || buffer[1] == 0)
		return (NULL);
	leftover = ft_substr(buffer, i + 1, (ft_strchr(buffer, 0) - buffer) - i);
	if (*leftover == 0)
	{
		free(leftover);
		leftover = NULL;
	}
	buffer[i + 1] = 0;
	return (leftover);
}

static char	*read_to_buff(int fd, char *buff_leftovers, char *buffer)
{
	ssize_t	read_len;
	char	*tmp;

	read_len = 1;
	while (read_len > 0)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len < 0)
		{
			free(buff_leftovers);
			return (NULL);
		}
		else if (read_len == 0)
			break ;
		buffer[read_len] = 0;
		if (!buff_leftovers)
			buff_leftovers = ft_strdup("");
		tmp = buff_leftovers;
		buff_leftovers = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (buff_leftovers);
}

char	*get_next_line(int fd)
{
	static char	*buff_leftovers[MAX_FD];
	char		*line_to_return;
	char		*buffer;

	buffer = ft_calloc((BUFFER_SIZE + 1), 1);
	if ((fd < 0 || fd > MAX_FD) || BUFFER_SIZE <= 0)
	{
		free(buff_leftovers[fd]);
		free(buffer);
		buff_leftovers[fd] = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line_to_return = read_to_buff(fd, buff_leftovers[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line_to_return)
	{
		buff_leftovers[fd] = NULL;
		return (NULL);
	}
	buff_leftovers[fd] = extract_line(line_to_return);
	return (line_to_return);
}
