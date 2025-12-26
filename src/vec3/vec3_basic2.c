/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basic2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:02:14 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 15:02:15 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	scale_vec3(t_vec3 v, double scalar)
{
	return (init_vec3(v.x * scalar, v.y * scalar, v.z * scalar));
}

t_vec3	divide_vec3(t_vec3 v, double scalar)
{
	return (scale_vec3(v, 1 / scalar));
}

t_vec3	negative_vec3(t_vec3 v)
{
	return (scale_vec3(v, -1));
}

t_vec3	multiply_vec3(t_vec3 a, t_vec3 b)
{
	return (init_vec3(a.x * b.x, a.y * b.y, a.z * b.z));
}
