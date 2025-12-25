/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 00:04:26 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 00:04:27 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "ray.h"
# include "vec3.h"

typedef struct s_camera
{
	t_vec3					origin;
	t_vec3					horizontal;
	t_vec3					vertical;
	t_vec3					right_dir;
	t_vec3					down_dir;
	t_vec3					top_left_corner;
}							t_camera;

typedef struct s_program	t_program;

t_camera					init_camera(t_vec3 look_from, t_vec3 direction,
								t_vec3 view_up, double hfov);
void						setup_camera(t_vec3 lookfrom, t_vec3 direction,
								double hfov, t_program *data);
t_ray						get_ray(t_camera camera, double x_offset,
								double y_offset);

#endif // !CAMERA_H
