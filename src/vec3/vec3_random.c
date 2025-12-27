/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_random.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:03:05 by squinn            #+#    #+#             */
/*   Updated: 2025/12/27 18:54:27 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <math.h>
#include <stdbool.h>

t_vec3	init_random_vec3(t_xorshift64_state *state)
{
	double	x;
	double	y;
	double	z;

	x = random_double(state);
	y = random_double(state);
	z = random_double(state);
	return (init_vec3(x, y, z));
}

t_vec3	init_random_vec3_range(t_xorshift64_state *state, double min,
		double max)
{
	double	x;
	double	y;
	double	z;

	x = random_double_range(state, min, max);
	y = random_double_range(state, min, max);
	z = random_double_range(state, min, max);
	return (init_vec3(x, y, z));
}

t_vec3	init_random_vec3_in_unit_sphere(t_xorshift64_state *state)
{
	t_vec3	result;

	while (true)
	{
		result = init_random_vec3_range(state, -1, 1);
		if (length_squared_vec3(result) >= 1)
			continue ;
		return (result);
	}
}

t_vec3	init_random_normalize_vec3(t_xorshift64_state *state)
{
	double	a;
	double	z;
	double	small_r;

	a = random_double_range(state, 0, 2 * M_PI);
	z = random_double_range(state, -1, 1);
	small_r = sqrt(1 - z * z);
	return (init_vec3(small_r * cos(a), small_r * sin(a), z));
}
