/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:04:46 by lperis            #+#    #+#             */
/*   Updated: 2024/11/01 18:30:56 by lperis           ###   ########.fr       */
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

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst)
		return ;
	last = ft_lstlast(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}

char *get_next_line(int fd)
{
	char *str;
	static char *buff;
	ssize_t readlength;
	int i;
	t_list *listass;
	t_list *new;

	listass = NULL;
	if(fd < 0)
		return(NULL);
	buff = calloc(BUFFER_SIZE + 1, 1);
	if(!buff)
		return (NULL);
	readlength = read(fd, buff, BUFFER_SIZE);
	while(readlength > 0)
	// saveline /savebuffer
	{		
			new = ft_lstnew(buff);
			ft_lstadd_back(&listass, new);
			buff = calloc(BUFFER_SIZE + 1, 1);
			readlength = read(fd, buff, BUFFER_SIZE);
	}
	printf("%s", listass->content);
	/*	else if(buff)
		{

		}*/
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
