/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:51:42 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 14:51:43 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

size_t	count_strings(char **strings)
{
	size_t	i;

	i = 0;
	while (strings[i] != NULL)
		i++;
	return (i);
}

void	free_strings(char **strings)
{
	int	i;

	if (strings == NULL)
		return ;
	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}
