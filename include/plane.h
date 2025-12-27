/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:33:00 by ikota             #+#    #+#             */
/*   Updated: 2025/12/27 14:33:01 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "material.h"
# include "range.h"
# include "vec3.h"

typedef struct s_plane
{
	t_vec3		point;
	t_vec3		normal;
	t_material	material;
}				t_plane;

t_plane			*new_plane(t_vec3 point, t_vec3 normal, t_material material);
bool			hits_plane(t_ray ray, t_range range, t_hit_record *hit_rec,
					t_plane *plane_ptr);

#endif
