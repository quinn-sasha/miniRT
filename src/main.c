/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 16:01:52 by squinn            #+#    #+#             */
/*   Updated: 2025/12/27 16:01:53 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculate_color.h"
#include "camera.h"
#include "color.h"
#include "hit_record.h"
#include "libft.h"
#include "light.h"
#include "material.h"
#include "minilibx_utils.h"
#include "minirt.h"
#include "mlx.h"
#include "object_list.h"
#include "parse.h"
#include "random_number_generator.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_color	calculate_average_color(t_program *data, int x, int y)
{
	t_color	pixel_color;
	double	x_offset;
	double	y_offset;
	t_ray	ray;
	int		sample;

	pixel_color = init_color(0, 0, 0);
	sample = 0;
	while (sample < data->num_samples)
	{
		x_offset = (x + random_double(&data->state)) / (WIDTH - 1);
		y_offset = (y + random_double(&data->state)) / (HEIGHT - 1);
		ray = get_ray(data->camera, x_offset, y_offset);
		pixel_color = add_vec3(pixel_color, calculate_color(ray, data,
					data->max_recursions));
		sample++;
	}
	pixel_color = divide_vec3(pixel_color, data->num_samples);
	return (pixel_color);
}

int	render(t_program *data)
{
	t_color	pixel_color;
	int		x;
	int		y;

	if (data->window == NULL)
		return (EXIT_SUCCESS);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_color = calculate_average_color(data, x, y);
			gamma_correction(&pixel_color);
			set_pixel_color(x, y, &data->img, rgb_to_integer(pixel_color));
			x++;
		}
		y++;
	}
	ft_putstr_fd("Rendering done\n", STDOUT_FILENO);
	mlx_put_image_to_window(data->mlx, data->window, data->img.mlx_img, 0, 0);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_program	data;

	parse(argc, argv, &data);
	init_mlx_resources(&data);
	set_mlx_hooks(&data);
	render(&data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
