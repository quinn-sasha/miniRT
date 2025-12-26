/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:40:46 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 14:40:47 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "vec3.h"

t_ray	init_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	new_ray;

	new_ray.origin = origin;
	new_ray.direction = normalize_vec3(direction);
	return (new_ray);
}

t_vec3	ray_at(t_ray ray, double t)
{
	return (add_vec3(ray.origin, scale_vec3(ray.direction, t)));
}
