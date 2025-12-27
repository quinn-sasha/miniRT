/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:32:20 by ikota             #+#    #+#             */
/*   Updated: 2025/12/27 14:32:21 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "hit_record.h"
# include "range.h"
# include "ray.h"
# include "vec3.h"
# include <stdbool.h>

typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
	t_material	material;
}				t_sphere;

t_sphere		*new_sphere(t_vec3 center, double radius, t_material material);
bool			hits_sphere(t_ray ray, t_range range, t_hit_record *hit_record,
					t_sphere sphere);

#endif // !SPHERE_H
