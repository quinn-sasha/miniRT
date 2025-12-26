/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_diffuse_specular.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 17:35:34 by ikota             #+#    #+#             */
/*   Updated: 2025/12/26 19:48:54 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "hit_record.h"
#include "light.h"
#include "minirt.h"
#include "vec3.h"
#include <math.h>

t_vec3	calculate_diffuse(t_light *light, t_hit_record *record,
		t_vec3 normalized_light_dir_vec)
{
	double	dot_nl;
	t_color	diffuse_light;
	t_color	diffuse;

	dot_nl = dot_vec3(record->normal_vector, normalized_light_dir_vec);
	if (dot_nl < 0)
		dot_nl = 0;
	diffuse_light = scale_vec3(light->color, light->brightness_ratio * dot_nl);
	diffuse = multiply_vec3(diffuse_light, record->material.albedo);
	return (diffuse);
}

#define SHININESS 32

t_vec3	calculate_specular(t_hit_record *record, t_light *light, t_ray ray,
		t_vec3 normalized_light_dir_vec)
{
	t_vec3	reflected;
	t_vec3	negative_ray_dir;
	double	dot_rn;
	t_color	specular_color;
	double	specular_factor;

	reflected = reflect(negative_vec3(normalized_light_dir_vec),
			record->normal_vector);
	negative_ray_dir = negative_vec3(ray.direction);
	dot_rn = dot_vec3(reflected, negative_ray_dir);
	if (dot_rn < 0)
		return (init_color(0, 0, 0));
	specular_color = multiply_vec3(light->color, record->material.albedo);
	specular_factor = pow(dot_rn, SHININESS);
	return (scale_vec3(specular_color, light->brightness_ratio
			* specular_factor));
}

t_color	calculate_diffuse_specular(t_program *data, t_hit_record *record,
					t_vec3 normalized_light_dir_vec, t_ray ray)
{
	t_color			diffuse;
	t_color			specular;

	diffuse = calculate_diffuse(&data->light, record, normalized_light_dir_vec);
	specular = init_color(0, 0, 0);
	if (record->material.type == MAT_METAL)
		specular = calculate_specular(record, &data->light, ray,
				normalized_light_dir_vec);
	return (add_vec3(diffuse, specular));
}
