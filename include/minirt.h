/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 19:06:45 by ikota             #+#    #+#             */
/*   Updated: 2025/12/26 19:06:46 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "camera.h"
# include "img.h"
# include "light.h"
# include "object_list.h"

# define WIDTH 384
# define HEIGHT 216

typedef struct s_program
{
	void			*mlx;
	void			*window;
	t_img			img;
	t_scene_object	head;
	t_camera		camera;
	t_ambient		ambient;
	t_light			light;
	int				max_recursions;
	int				num_samples_per_pixel;
}					t_program;

#endif
