/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:24:20 by ikota             #+#    #+#             */
/*   Updated: 2025/09/21 14:46:54 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

size_t	ft_strlen_gnl(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strjoin_gnl(char	*s1, char	*s2)
{
	char	*new_str;
	char	*tmp;
	char	*origin_s1;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		*s1 = '\0';
	}
	if (!s2)
		return (s1);
	origin_s1 = s1;
	new_str = malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (!new_str)
		return (free(s1), NULL);
	tmp = new_str;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	free(origin_s1);
	return (new_str);
}

char	*ft_strchr_gnl(const	char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy_gnl(void	*dest, const void	*src, size_t n)
{
	unsigned char	*unchar_dest;
	unsigned char	*unchar_src;

	unchar_dest = (unsigned char *)dest;
	unchar_src = (unsigned char *)src;
	while (n)
	{
		*unchar_dest++ = *unchar_src++;
		n--;
	}
	return (dest);
}

//join connect buffers
//find position of chr '\n'
//memcpy copy
//sub copy only necessary parts
//conditional expressions (while, if, etc.) are treated with the rule
//that they are null or not, so you can return pointers
//join but in the first loop buf is NULL, so you can't write to it, and
//it crashes if you try to write to it. Segfo
