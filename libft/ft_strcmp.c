/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 00:07:32 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 00:07:33 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (s1 == s2)
		return (0);
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
		{
			return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
		}
		s1++;
		s2++;
	}
	return (0);
}
