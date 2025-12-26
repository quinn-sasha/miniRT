/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:41:12 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 14:41:13 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vec3.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}			t_ray;

t_ray		init_ray(t_vec3 origin, t_vec3 direction);
t_vec3		ray_at(t_ray ray, double t);

#endif // !RAY_H
