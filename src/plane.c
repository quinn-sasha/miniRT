/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:09:43 by ikota             #+#    #+#             */
/*   Updated: 2025/12/26 15:09:44 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit_record.h"
#include "plane.h"
#include "range.h"
#include "xmalloc.h"
#include <math.h>
#include <stdlib.h>

t_plane	*new_plane(t_vec3 point, t_vec3 normal, t_material material)
{
	t_plane	*new_plane;

	new_plane = xmalloc(sizeof(t_plane));
	new_plane->point = point;
	new_plane->normal = normalize_vec3(normal);
	new_plane->material = material;
	return (new_plane);
}

bool	hits_plane(const t_ray ray, t_range range, t_hit_record *record,
		t_plane *plane)
{
	double	denom;
	t_vec3	tmp;
	double	numerator;
	double	t;

	denom = dot_vec3(ray.direction, plane->normal);
	if (fabs(denom) < 1e-6)
		return (false);
	tmp = sub_vec3(plane->point, ray.origin);
	numerator = dot_vec3(tmp, plane->normal);
	t = numerator / denom;
	if (t < range.min_t || t > range.max_t)
		return (false);
	record->t = t;
	record->intersection = ray_at(ray, t);
	set_fronts_face_and_normal_vector(record, ray, plane->normal);
	record->material = plane->material;
	return (true);
}
