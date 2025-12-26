/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 00:14:58 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 00:16:10 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "math.h"
#include "utilities.h"
#include "vec3.h"
#include <stdio.h>

t_color	init_color(double red, double green, double blue)
{
	t_color	color;

	color.x = clamp(red, 0.0, 1.0);
	color.y = clamp(green, 0.0, 1.0);
	color.z = clamp(blue, 0.0, 1.0);
	return (color);
}

void	gamma_correction(t_color *color)
{
	color->x = sqrt(color->x);
	color->y = sqrt(color->y);
	color->z = sqrt(color->z);
}

uint32_t	rgb_to_integer(t_color color)
{
	int		r;
	int		g;
	int		b;

	r = 256 * clamp(color.x, 0.0, 0.999);
	g = 256 * clamp(color.y, 0.0, 0.999);
	b = 256 * clamp(color.z, 0.0, 0.999);
	return (r << 16 | g << 8 | b);
}

t_color	clamp_color(t_color color)
{
	t_color	res;

	res.x = clamp(color.x, 0.0, 1.0);
	res.y = clamp(color.y, 0.0, 1.0);
	res.z = clamp(color.z, 0.0, 1.0);
	return (res);
}
