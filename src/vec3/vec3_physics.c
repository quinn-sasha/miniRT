/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_physics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:02:44 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 15:02:45 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <math.h>

t_vec3	reflect(t_vec3 incoming, t_vec3 normal)
{
	double	temp;

	temp = dot_vec3(incoming, normal);
	return (add_vec3(incoming, scale_vec3(normal, -2 * temp)));
}

t_vec3	refract(t_vec3 incoming, t_vec3 n, double eta_in_over_etat)
{
	double	cos_theta;
	t_vec3	parallel;
	double	scalar;
	t_vec3	perpendicular;

	cos_theta = -dot_vec3(incoming, n);
	parallel = scale_vec3(add_vec3(incoming, scale_vec3(n, cos_theta)),
			eta_in_over_etat);
	scalar = -sqrt(1.0 - length_squared_vec3(parallel));
	perpendicular = scale_vec3(n, scalar);
	return (add_vec3(parallel, perpendicular));
}
