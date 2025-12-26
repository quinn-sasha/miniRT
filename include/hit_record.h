/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 00:23:45 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 00:29:16 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_RECORD_H
# define HIT_RECORD_H

# include "material.h"
# include "ray.h"
# include "vec3.h"
# include <stdbool.h>

typedef struct s_hit_record	t_hit_record;

struct						s_hit_record
{
	t_vec3					intersection;
	t_vec3					normal_vector;
	double					t;
	bool					fronts_face;
	t_material				material;
};

void	set_fronts_face_and_normal_vector(t_hit_record *record, t_ray ray,
			t_vec3 outward_normal_vector);

#endif
