/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:04:46 by lperis            #+#    #+#             */
/*   Updated: 2024/11/05 19:02:35 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *) s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*cast_src;
	char		*cast_dest;
	size_t		i;

	i = 0;
	if (src == NULL && dest == NULL)
		return (0);
	cast_src = (char *) src;
	cast_dest = (char *) dest;
	while (i < n)
	{
		cast_dest[i] = cast_src[i];
		i++;
	}
	return (cast_dest);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			max;
	void			*ptr;

	max = -1;
	if (size != 0 && nmemb > max / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		s1_length;
	int		s2_length;
	
	if (!s1 || !s2)
		return (NULL);
	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1_length + s2_length) + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1_length);
	ft_memcpy(str + s1_length, s2, s2_length + 1);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	c = (unsigned char)c;
	while (*s != c && *s)
		s++;
	if (c == *s)
		return ((char *)s);
	return (NULL);
}

char *check_n(char *buff)
{
	int i;
	i = 0;
	while(buff[i] != '\n' && buff[i] != '\0')
		i++;	
	return(buff);
}

char *empty_buffer(char *buff)
{
	char *tmp;
	int i;
	i = 0;
	while(buff[i] != '\n' && buff[i] != '\0')
		i++;
	i++;
	tmp = ft_calloc(ft_strlen(buff) - i + 1, 1);
	int j;
	j = 0;
	while(buff[i] != '\0')
	{
		tmp[j] = buff[i];
		i++;
		j++;
	}
	free (buff);
	return (tmp);
}

int r_line(int fd, char **buff)
{
	char *read_line;
	int	read_length;
	
	read_length = 1;
	read_line = ft_calloc(BUFFER_SIZE + 1, 1);
	if(!read_line)
			return (-1);
	while(read_length > 0)
	{
		read_length = read(fd, read_line, BUFFER_SIZE);
		*buff = ft_strjoin(*buff, read_line);
		if (ft_strchr(*buff, '\n'))
			break ;
	}
	if (read_length <= 0)
		free(read_line);
	return(read_length);
}

char *get_line(char *buff)
{
	char *line;
	int i;
	i = 0;
	line = ft_calloc(ft_strlen(buff) + 1, 1);	
	while(buff[i] != '\n' && buff[i] != '\0')
	{
		line[i] = buff[i];
		i++;
	}
	if(buff[i] == '\n')
		line[i] = buff[i];
	return(line);	
}

char *get_next_line(int fd)
{
	static char *buff;
	char *acc;
	int rl;

	if(!buff)
		buff = ft_calloc(BUFFER_SIZE , 1);
	if(!buff)
		return(NULL);
	if(ft_strchr(buff, '\n'))
	{
		acc = check_n(buff);
		return(acc);
	}
	if(fd < 0)
		return(NULL);
	acc = ft_calloc(BUFFER_SIZE, 1);
	if(!acc)
		return (NULL);
	rl = r_line(fd, &buff);
	if (rl == 0)
			return (NULL);
	if(!buff)
		return (NULL);
	acc = get_line(buff);
	buff = empty_buffer(buff);
	return(acc);
}

int main(void)
{	
	int fd = open("text", O_RDONLY);
	char *str = NULL;
	do
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
	} while (str);
	close(fd);
}
