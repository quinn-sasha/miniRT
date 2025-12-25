/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 01:06:51 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 01:08:00 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "random_number_generator.h"
# include "ray.h"
# include <stdbool.h>

typedef struct s_hit_record	t_hit_record;

typedef enum e_material_type
{
	MAT_LAMBERTIAN,
	MAT_METAL,
	MAT_DIELECTRIC,
}							t_material_type;

typedef struct s_material
{
	t_material_type			type;
	t_color					albedo;
	union					u_data
	{
		double				fuzziness;
		double				refractive_index;
	} data;
}							t_material;

// init_material.c
t_material					init_lambertian_material(t_color albedo);
t_material					init_metal_material(t_color albedo,
								double fuzziness);
t_material					init_dielectric_material(double refractive_index);
// material.c
bool						lambertian_scatters(t_hit_record record,
								t_ray *scattered, t_xorshift64_state *state);
bool						metal_scatters(t_ray ray, t_hit_record record,
								t_ray *scattered, t_xorshift64_state *state);
bool						dielectric_scatters(t_ray ray, t_hit_record record,
								t_ray *scattered, t_xorshift64_state *state);

#endif // !MATERIAL_H
