/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:34:46 by ikota             #+#    #+#             */
/*   Updated: 2025/12/25 20:10:35 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "random_number_generator.h"
# include "ray.h"
# include <stdbool.h>

typedef struct s_hit_record	t_hit_record;

typedef enum
{
	MAT_LAMBERTIAN,
	MAT_METAL,
	MAT_DIELECTRIC,
}							e_material_type;

typedef struct s_material
{
	e_material_type			type;
	t_color albedo; // dielectric deosn't have albedo
	union					data
	{
		double fuzziness;        // 0 ~ 1 (metal)
		double refractive_index; // Not air (dielectric)
	} data;
}							t_material;

bool						lambertian_scatters(t_hit_record record,
								t_ray *scattered, t_xorshift64_state *state);
bool						metal_scatters(t_ray ray, t_hit_record record,
								t_ray *scattered, t_xorshift64_state *state);
bool						dielectric_scatters(t_ray ray, t_hit_record record,
								t_ray *scattered, t_color *attenuation,
								t_xorshift64_state *state);
t_material					init_lambertian_material(t_color albedo);
t_material					init_metal_material(t_color albedo,
								double fuzziness);
t_material					init_dielectric_material(double refractive_index);

#endif // !MATERIAL_H
