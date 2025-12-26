/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:03:25 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 15:03:59 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <math.h>

double	length_squared_vec3(t_vec3 v)
{
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

double	length_vec3(t_vec3 v)
{
	return (sqrt(length_squared_vec3(v)));
}

double	dot_vec3(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	normalize_vec3(t_vec3 v)
{
	double	length;

	length = length_vec3(v);
	return (scale_vec3(v, 1 / length));
}

t_vec3	cross_vec3(t_vec3 a, t_vec3 b)
{
	return (init_vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y
			- a.y * b.x));
}
