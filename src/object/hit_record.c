/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 00:23:00 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 00:23:01 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit_record.h"

void	set_fronts_face_and_normal_vector(t_hit_record *record, t_ray ray,
		t_vec3 outward_normal_vector)
{
	if (dot_vec3(ray.direction, outward_normal_vector) > 0.0)
	{
		record->fronts_face = false;
		record->normal_vector = scale_vec3(outward_normal_vector, -1);
		return ;
	}
	record->fronts_face = true;
	record->normal_vector = outward_normal_vector;
}
