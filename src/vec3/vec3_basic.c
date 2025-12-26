/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:01:56 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 15:01:57 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "random_number_generator.h"
#include "vec3.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

t_vec3	init_vec3(double x, double y, double z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_vec3	add_vec3(t_vec3 a, t_vec3 b)
{
	return (init_vec3(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	add_triple_vec3(t_vec3 a, t_vec3 b, t_vec3 c)
{
	return (add_vec3(a, add_vec3(b, c)));
}

t_vec3	sub_vec3(t_vec3 a, t_vec3 b)
{
	return (init_vec3(a.x - b.x, a.y - b.y, a.z - b.z));
}
