/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 00:19:32 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 00:19:33 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_utils.h"
#include "libft.h"
#include "minilibx_utils.h"
#include "parse.h"
#include "utilities.h"
#include <stdlib.h>

void	print_error(const char *message)
{
	ft_printf("Error: %s\n", message);
}

int	error_return(const char *message, int status)
{
	print_error(message);
	return (status);
}

void	error_exit(const char *message)
{
	ft_printf("Error: %s\n", message);
	exit(EXIT_FAILURE);
}

void	handle_mlx_error(t_program *data)
{
	destroy_mlx_resources_if_allocated(data);
	error_exit(MLX_ERROR);
}

int	handle_parse_error(char **strings)
{
	free_strings(strings);
	return (PARSE_FAILED);
}
