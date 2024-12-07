/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:58:48 by lperis            #+#    #+#             */
/*   Updated: 2024/11/14 12:27:30 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
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
	char			*str;
	size_t			i;

	i = 0;
	max = -1;
	if (size != 0 && nmemb > max / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	str = (char *) ptr;
	while (i < nmemb * size)
	{
		str[i] = '\0';
		i++;
	}
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
