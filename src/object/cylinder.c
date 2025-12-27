/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 20:28:16 by ikota             #+#    #+#             */
/*   Updated: 2025/12/27 16:09:02 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "hit_record.h"
#include "math_utils.h"
#include "range.h"
#include "xmalloc.h"
#include <math.h>
#include <stdlib.h>

t_cylinder	*new_cylinder(t_vec3 *vectors, double *dimensions,
		t_material material)
{
	t_cylinder	*new_cylinder;

	new_cylinder = xmalloc(sizeof(t_cylinder));
	new_cylinder->center = vectors[0];
	new_cylinder->axis = vectors[1];
	new_cylinder->radius = dimensions[0];
	new_cylinder->height = dimensions[1];
	new_cylinder->material = material;
	return (new_cylinder);
}

static t_ray	world_to_local_ray(t_ray ray, t_vec3 center, t_basis basis)
{
	t_vec3	origin_diff;
	t_ray	local_ray;

	origin_diff = sub_vec3(ray.origin, center);
	local_ray.origin = init_vec3(dot_vec3(origin_diff, basis.ex),
			dot_vec3(origin_diff, basis.ey), dot_vec3(origin_diff, basis.ez));
	local_ray.direction = init_vec3(dot_vec3(ray.direction, basis.ex),
			dot_vec3(ray.direction, basis.ey), dot_vec3(ray.direction,
				basis.ez));
	return (local_ray);
}

bool	hit_cylinder(const t_ray ray, t_range range, t_hit_record *record,
		const t_cylinder *cyl)
{
	t_vec3	tmp;
	t_basis	basis;
	t_ray	local_ray;
	t_vec3	local_n;

	basis.ey = normalize_vec3(cyl->axis);
	tmp = init_vec3(0, 0, 0);
	if (fabs(basis.ey.y) < 0.9)
		tmp = init_vec3(0, 1, 0);
	else
		tmp = init_vec3(1, 0, 0);
	basis.ex = normalize_vec3(cross_vec3(tmp, basis.ey));
	basis.ez = cross_vec3(basis.ex, basis.ey);
	local_ray = world_to_local_ray(ray, cyl->center, basis);
	if (!hit_cylinder_side_cap(local_ray, range, record, cyl))
		return (false);
	local_n = record->normal_vector;
	record->normal_vector = add_triple_vec3(scale_vec3(basis.ex, local_n.x),
			scale_vec3(basis.ey, local_n.y), scale_vec3(basis.ez, local_n.z));
	record->intersection = ray_at(ray, record->t);
	set_fronts_face_and_normal_vector(record, ray, record->normal_vector);
	return (true);
}
