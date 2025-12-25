/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 00:55:51 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 00:55:52 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "hit_record.h"
#include "material.h"
#include "random_number_generator.h"
#include "utilities.h"
#include "vec3.h"
#include <math.h>

bool	lambertian_scatters(t_hit_record record, t_ray *scattered,
		t_xorshift64_state *state)
{
	t_vec3	scatter_direction;

	scatter_direction = add_vec3(record.normal_vector,
			init_random_normalize_vec3(state));
	*scattered = init_ray(record.intersection, scatter_direction);
	return (true);
}

bool	metal_scatters(t_ray ray, t_hit_record record, t_ray *scattered,
		t_xorshift64_state *state)
{
	t_vec3	reflected;
	t_vec3	direction;

	reflected = reflect(normalize_vec3(ray.direction), record.normal_vector);
	direction = add_vec3(reflected,
			scale_vec3(init_random_vec3_in_unit_sphere(state),
				record.material.data.fuzziness));
	*scattered = init_ray(record.intersection, direction);
	return (dot_vec3(reflected, record.normal_vector) > 0);
}

static double	schlick_reflectivity(double eta_in_over_etat, double cos_theta)
{
	double	f0;

	f0 = (1 - eta_in_over_etat) / (1 + eta_in_over_etat);
	f0 = f0 * f0;
	return (f0 + (1 - f0) * pow(1 - cos_theta, 5));
}

static bool	will_reflect(double eta_in_over_etat, double cos_theta,
		t_xorshift64_state *state)
{
	double	sin_theta;
	double	reflectivity;

	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	if (eta_in_over_etat * sin_theta > 1.0)
		return (true);
	reflectivity = schlick_reflectivity(eta_in_over_etat, cos_theta);
	if (reflectivity > random_double(state))
		return (true);
	return (false);
}

bool	dielectric_scatters(t_ray ray, t_hit_record record, t_ray *scattered,
		t_xorshift64_state *state)
{
	const double	refractive_index = record.material.data.refractive_index;
	double			eta_in_over_etat;
	double			cos_theta;
	t_vec3			reflected;
	t_vec3			refracted;

	if (record.fronts_face)
		eta_in_over_etat = 1.0 / refractive_index;
	else
		eta_in_over_etat = refractive_index;
	cos_theta = min_double(dot_vec3(negative_vec3(ray.direction),
				record.normal_vector), 1.0);
	if (will_reflect(eta_in_over_etat, cos_theta, state))
	{
		reflected = reflect(ray.direction, record.normal_vector);
		*scattered = init_ray(record.intersection, reflected);
		return (true);
	}
	refracted = refract(ray.direction, record.normal_vector, eta_in_over_etat);
	*scattered = init_ray(record.intersection, refracted);
	return (true);
}
