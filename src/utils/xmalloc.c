/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:13:19 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 15:13:20 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_utils.h"
#include "xmalloc.h"
#include <stdlib.h>

void	*xmalloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (result == NULL)
	{
		error_exit("xmalloc()");
	}
	return (result);
}
