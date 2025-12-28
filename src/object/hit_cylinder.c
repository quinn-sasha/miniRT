/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:00:36 by ikota             #+#    #+#             */
/*   Updated: 2025/12/28 22:09:45 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "hit_record.h"
#include "math_utils.h"
#include "range.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>

static bool	hit_cylinder_side(const t_ray ray, t_range range,
		t_hit_record *record, const t_cylinder *cyl)
{
	t_quadratic	quadratic;
	t_vec3		intersection;
	double		half_h;
	t_vec3		outward_normal_vector;

	quadratic = prepare_quadratic_cylinder(ray, cyl);
	record->t = solve_quadratic_t(quadratic, range);
	if (record->t == false)
		return (false);
	intersection = ray_at(ray, record->t);
	half_h = cyl->height / 2.0;
	if (intersection.y < -half_h || intersection.y > half_h)
		return (false);
	record->intersection = intersection;
	outward_normal_vector = init_vec3((record->intersection.x - cyl->center.x)
			/ cyl->radius, 0, (record->intersection.z - cyl->center.z)
			/ cyl->radius);
	set_fronts_face_and_normal_vector(record, ray, outward_normal_vector);
	record->material = cyl->material;
	return (true);
}

static bool	hit_cylinder_cap(const t_ray ray, t_range range,
		t_hit_record *record, const t_cylinder *cyl)
{
	double	t;
	t_vec3	intersection;
	t_vec3	outward_normal_vector;

	if (fabs(ray.direction.y) < 1e-6)
		return (false);
	t = (cyl->center.y - ray.origin.y) / ray.direction.y;
	if (t < range.min_t || t > range.max_t)
		return (false);
	intersection = ray_at(ray, t);
	if ((intersection.x * intersection.x + intersection.z
			* intersection.z) > cyl->radius * cyl->radius)
		return (false);
	record->t = t;
	record->intersection = intersection;
	outward_normal_vector = init_vec3(0, 0, 0);
	if (cyl->center.y > 0)
		outward_normal_vector = init_vec3(0, 1.0, 0);
	else
		outward_normal_vector = init_vec3(0, -1.0, 0);
	set_fronts_face_and_normal_vector(record, ray, outward_normal_vector);
	record->material = cyl->material;
	return (true);
}

static bool	record_hit(bool *hit_anything, double *closest_so_far,
		t_hit_record *record)
{
	*hit_anything = true;
	*closest_so_far = record->t;
	return (true);
}

bool	hit_cylinder_side_cap(t_ray local_ray, t_range range,
		t_hit_record *record, const t_cylinder *cyl)
{
	bool		hit_anything;
	double		closest_so_far;
	t_cylinder	local_cyl;

	hit_anything = false;
	local_cyl = *cyl;
	local_cyl.center = init_vec3(0, 0, 0);
	if (hit_cylinder_side(local_ray, range, record, &local_cyl))
		hit_anything = record_hit(&hit_anything, &closest_so_far, record);
	local_cyl.center.y = -cyl->height / 2.0;
	if (hit_cylinder_cap(local_ray, range, record, &local_cyl))
		hit_anything = record_hit(&hit_anything, &closest_so_far, record);
	local_cyl.center.y = cyl->height / 2.0;
	if (hit_cylinder_cap(local_ray, range, record, &local_cyl))
		hit_anything = record_hit(&hit_anything, &closest_so_far, record);
	return (hit_anything);
}
