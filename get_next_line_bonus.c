/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:26:44 by lperis            #+#    #+#             */
/*   Updated: 2024/11/16 16:19:41 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	empty_buffer(char **buff, int size)
{
	int	j;

	j = 0;
	while (buff[0][size + j])
	{
		buff[0][j] = buff[0][size + j];
		j++;
	}
	buff[0][j] = '\0';
}

char	*_get_line(char **buff)
{
	char	*line;
	int		size;
	int		j;

	line = NULL;
	size = 0;
	j = 0;
	while (buff[0][size] != '\n' && buff[0][size] != '\0')
		size++;
	if (buff[0][size] == '\n')
		size++;
	line = ft_calloc(size + 2, 1);
	if (!line)
		return (NULL);
	while (j < size)
	{
		line[j] = buff[0][j];
		j++;
	}
	empty_buffer(buff, size);
	return (line);
}

int	r_line(int fd, char **buff)
{
	char	*buffer;
	char	*tmp;
	int		read_length;

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (0);
	read_length = 1;
	while (read_length > 0)
	{
		read_length = read(fd, buffer, BUFFER_SIZE);
		if (read_length >= 0)
		{
			buffer[read_length] = '\0';
			tmp = ft_strjoin(*buff, buffer);
			free(*buff);
			*buff = tmp;
			if (ft_strchr(*buff, '\n'))
				break ;
		}
	}
	free(buffer);
	return (read_length);
}

char	*get_next_line(int fd)
{
	static char	*buff[1024];
	char		*result;
	int			rl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buff[fd])
		buff[fd] = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buff[fd])
		return (NULL);
	rl = r_line(fd, &buff[fd]);
	result = _get_line(&buff[fd]);
	if (rl <= 0 && !result[0])
	{
		free (result);
		free (buff[fd]);
		buff[fd] = NULL;
		result = NULL;
		return (NULL);
	}
	return (result);
}

#include<stdio.h>

int main(void)
{
	int fd =  open ("text", O_RDONLY);
	char *str = NULL;
	do {
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
	} while(str);
	close (fd);
}
