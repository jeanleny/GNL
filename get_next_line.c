/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:04:46 by lperis            #+#    #+#             */
/*   Updated: 2024/11/01 17:49:17 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*element;

	element = malloc(sizeof (*element));
	if (!element)
		return (NULL);
	element->content = content;
	element->next = NULL;
	return (element);
}

char *get_next_line(int fd)
{
	char *str;
	static char *buff;
	ssize_t readlength;
	int i;
	t_list *listass;

	if(fd < 0)
		return(NULL);
	buff = calloc(BUFFER_SIZE + 1, 1);
	if(!buff)
		return (NULL);
	readlength = read(fd, buff, BUFFER_SIZE);
	listass = ft_lstnew(buff);
	while(readlength > 0)
	// saveline /savebuffer
	{		
		
		readlength = read(fd, buff, BUFFER_SIZE);
	}
	if(readlength == -1)
	{
		free (buff);	
		return(NULL);
	}
	str = calloc(BUFFER_SIZE + 1, 1);
	if(!str)
		return (NULL);
	i = 0;
	while(buff[i] != '\n' && buff[i] != '\0')
	{
		str[i] = buff[i];
		i++;
	}
	printf("%lu", strlen(str));
	return(str);
}

int main(void)
{	
	int fd = open("text", O_RDONLY);
	char *tofree = get_next_line(fd);
	printf("%s", tofree);
	free (tofree);

}
