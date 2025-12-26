/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:10:07 by ikota             #+#    #+#             */
/*   Updated: 2025/12/26 16:19:40 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit_record.h"
#include "math_utils.h"
#include "range.h"
#include "sphere.h"
#include "vec3.h"
#include "xmalloc.h"
#include <math.h>
#include <stdlib.h>

t_sphere	*new_sphere(t_vec3 center, double radius, t_material material)
{
	t_sphere	*new_sphere;

	new_sphere = xmalloc(sizeof(t_sphere));
	new_sphere->center = center;
	new_sphere->radius = radius;
	new_sphere->material = material;
	return (new_sphere);
}

// TODO: 他の衝突判定関数に合わせて、t_sphere型からt_sphere *型にする
bool	hits_sphere(t_ray ray, t_range range, t_hit_record *record,
		t_sphere sphere)
{
	t_quadratic	quadratic;
	t_vec3		outward_normal_vector;

	quadratic = prepare_quadratic_sphere(ray, sphere);
	record->t = solve_quadratic_t(quadratic, range);
	if (record->t == false)
		return (false);
	record->intersection = ray_at(ray, record->t);
	outward_normal_vector = divide_vec3(sub_vec3(record->intersection,
				sphere.center), sphere.radius);
	set_fronts_face_and_normal_vector(record, ray, outward_normal_vector);
	record->material = sphere.material;
	return (true);
}
