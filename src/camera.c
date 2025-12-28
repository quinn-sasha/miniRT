/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 20:26:48 by squinn            #+#    #+#             */
/*   Updated: 2025/12/28 22:45:01 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "math_utils.h"
#include "minirt.h"
#include "ray.h"
#include "utilities.h"
#include "vec3.h"
#include <math.h>

#define FOCAL_LENGTH 1.0

static void	set_viewport_width_height(double *width, double *height,
		double hfov)
{
	double			theta;
	double			width_scaling;
	const double	aspect_ratio = (double)WIDTH / HEIGHT;

	theta = degrees_to_radians(hfov);
	width_scaling = tan(theta / 2);
	*width = 2.0 * width_scaling;
	*height = *width / aspect_ratio;
}

static t_vec3	calculate_top_left_corner(t_vec3 origin, t_vec3 horizontal,
		t_vec3 down_vertical, t_vec3 direction)
{
	t_vec3	half_horizontal;
	t_vec3	half_vertical;
	t_vec3	z_componet;
	t_vec3	result;

	half_horizontal = divide_vec3(horizontal, 2);
	half_vertical = divide_vec3(down_vertical, -2);
	z_componet = scale_vec3(direction, FOCAL_LENGTH);
	result = sub_vec3(origin, half_horizontal);
	result = add_vec3(result, half_vertical);
	result = add_vec3(result, z_componet);
	return (result);
}

t_camera	init_camera(t_vec3 look_from, t_vec3 direction, t_vec3 view_up,
		double hfov)
{
	t_camera	camera;
	double		viewport_width;
	double		viewport_height;
	t_vec3		back_dir;

	camera.origin = look_from;
	set_viewport_width_height(&viewport_width, &viewport_height, hfov);
	back_dir = negative_vec3(direction);
	camera.right_dir = normalize_vec3(cross_vec3(back_dir, view_up));
	camera.down_dir = normalize_vec3(cross_vec3(back_dir, camera.right_dir));
	camera.horizontal = scale_vec3(camera.right_dir, viewport_width);
	camera.vertical = scale_vec3(camera.down_dir, viewport_height);
	camera.top_left_corner = calculate_top_left_corner(look_from,
			camera.horizontal, camera.vertical, direction);
	return (camera);
}

void	setup_camera(t_vec3 lookfrom, t_vec3 direction, double hfov,
		t_program *data)
{
	t_vec3	view_up;

	view_up = init_vec3(0, 1, 0);
	if (ft_fabs(direction.x) < 1e-6 && ft_fabs(direction.z) < 1e-6) {
		view_up = init_vec3(0, 0, 1);
		if (direction.y > 0)
			view_up = init_vec3(0, 0, -1);
	}
	data->camera = init_camera(lookfrom, direction, view_up, hfov);
}

t_ray	get_ray(t_camera camera, double x_offset, double y_offset)
{
	t_vec3	offset_from_top_left;
	t_vec3	direction;
	t_ray	ray;

	offset_from_top_left = add_triple_vec3(camera.top_left_corner,
			scale_vec3(camera.horizontal, x_offset), scale_vec3(camera.vertical,
				y_offset));
	direction = sub_vec3(offset_from_top_left, camera.origin);
	ray = init_ray(camera.origin, direction);
	return (ray);
}
