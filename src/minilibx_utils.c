/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:25:50 by squinn            #+#    #+#             */
/*   Updated: 2025/12/27 14:25:47 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_utils.h"
#include "minilibx_utils.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	init_mlx_resources(t_program *data)
{
	t_img	*image;

	data->mlx = NULL;
	data->window = NULL;
	data->img.mlx_img = NULL;
	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit(MLX_ERROR);
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	if (!data->window)
		handle_mlx_error(data);
	data->img.mlx_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.mlx_img)
		handle_mlx_error(data);
	image = &data->img;
	image->address = mlx_get_data_addr(image->mlx_img, &image->bits_per_pixel,
			&image->row_size, &image->endian);
	(void)image->endian;
}

void	destroy_mlx_resources_if_allocated(t_program *data)
{
	if (data->img.mlx_img)
	{
		mlx_destroy_image(data->mlx, data->img.mlx_img);
	}
	if (data->window)
	{
		mlx_destroy_window(data->mlx, data->window);
	}
	free(data->mlx);
}

int	destroy_window(t_program *data)
{
	mlx_destroy_window(data->mlx, data->window);
	data->window = NULL;
	destroy_mlx_resources_if_allocated(data);
	destroy_object_list(&data->head);
	exit(EXIT_SUCCESS);
}

static int	handle_keypress(int keysymbol, t_program *data)
{
	if (keysymbol == XK_ESCAPE)
		return (destroy_window(data));
	return (0);
}

void	set_mlx_hooks(t_program *data)
{
	mlx_hook(data->window, KEYPRESS, KEYPRESSMASK, handle_keypress, data);
	mlx_hook(data->window, DESTROYNOTIFY, 0, destroy_window, data);
}
