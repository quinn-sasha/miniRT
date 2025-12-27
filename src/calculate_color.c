/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 17:47:15 by ikota             #+#    #+#             */
/*   Updated: 2025/12/26 19:37:18 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculate_color.h"
#include "color.h"
#include "hit_record.h"
#include "light.h"
#include "minirt.h"
#include "object_list.h"
#include "vec3.h"
#include <math.h>

t_color	calculate_direct_lighting(t_hit_record *record, t_program *data,
		t_ray ray, t_range range)
{
	t_vec3			light_dir_vec;
	t_vec3			normalized_light_dir_vec;
	t_ray			shadow_ray;
	t_hit_record	shadow_rec;
	t_color			add_diffuse_specular;

	light_dir_vec = sub_vec3(data->light.pos, record->intersection);
	range.max_t = length_vec3(light_dir_vec);
	normalized_light_dir_vec = normalize_vec3(light_dir_vec);
	shadow_ray = init_ray(record->intersection, normalized_light_dir_vec);
	if (hits_any_object(&data->head, shadow_ray, range, &shadow_rec))
		return (init_color(0, 0, 0));
	add_diffuse_specular = calculate_diffuse_specular(data, record,
			normalized_light_dir_vec, ray);
	return (add_diffuse_specular);
}

t_color	calculate_indirect_lighting(t_hit_record record, t_ray ray,
		t_program *data, int num_recursions)
{
	t_ray	scattered;
	t_color	attenuation;
	t_color	indirect_light;
	bool	can_scatter;
	t_color	recursive_color;

	attenuation = record.material.albedo;
	indirect_light = init_color(0, 0, 0);
	can_scatter = false;
	if (record.material.type == MAT_LAMBERTIAN)
		can_scatter = lambertian_scatters(record, &scattered, &data->state);
	else if (record.material.type == MAT_METAL)
		can_scatter = metal_scatters(ray, record, &scattered, &data->state);
	else if (record.material.type == MAT_DIELECTRIC)
	{
		can_scatter = dielectric_scatters(ray, record, &scattered,
				&data->state);
		attenuation = init_color(1.0, 1.0, 1.0);
	}
	if (can_scatter)
	{
		recursive_color = calculate_color(scattered, data, num_recursions - 1);
		indirect_light = multiply_vec3(recursive_color, attenuation);
	}
	return (indirect_light);
}

t_color	calculate_ambient_color(t_program *data, t_hit_record record)
{
	t_color	ambient_effect;
	t_color	ambient_color;

	ambient_effect = scale_vec3(data->ambient.color, data->ambient.ratio);
	ambient_color = multiply_vec3(record.material.albedo, ambient_effect);
	return (ambient_color);
}

t_color	calculate_background_color(t_ray ray)
{
	double	t;
	t_color	white;

	t = 0.5 * (ray.direction.y + 1.0);
	white = init_color(1.0, 1.0, 1.0);
	return (add_vec3(scale_vec3(white, (1.0 - t)), scale_vec3(init_color(0.5,
					0.7, 1.0), t)));
}

t_color	calculate_color(t_ray ray, t_program *data, int num_recursions)
{
	t_hit_record	record;
	t_color			direct_light;
	t_color			indirect_light;
	t_color			ambient_color;
	t_range			range;

	if (num_recursions <= 0)
		return (init_color(0, 0, 0));
	range.min_t = 0.001;
	range.max_t = INFINITY;
	if (hits_any_object(&data->head, ray, range, &record))
	{
		direct_light = init_color(0, 0, 0);
		if (record.material.type == MAT_LAMBERTIAN
			|| record.material.type == MAT_METAL)
			direct_light = calculate_direct_lighting(&record, data, ray, range);
		indirect_light = calculate_indirect_lighting(record, ray, data,
				num_recursions);
		ambient_color = calculate_ambient_color(data, record);
		return (clamp_color(add_triple_vec3(direct_light, indirect_light,
					ambient_color)));
	}
	return (calculate_background_color(ray));
}
