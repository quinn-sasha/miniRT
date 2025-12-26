/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:51:20 by squinn            #+#    #+#             */
/*   Updated: 2025/12/25 18:55:28 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "error_utils.h"
#include "ft_atof.h"
#include "libft.h"
#include "material.h"
#include "parse.h"
#include "parse_utils.h"
#include "utilities.h"
#include "vec3.h"

#define EPSILON 1e-3

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
int	parse_color(const char *str, t_color *color)
{
	char	**colors;
	int		i;
	double	r;
	double	g;
	double	b;

	colors = ft_split(str, ',');
	if (count_strings(colors) != 3)
		return (handle_parse_error(colors));
	i = 0;
	while (colors[i])
	{
		if (!is_unsigned_int(colors[i]))
			return (handle_parse_error(colors));
		i++;
	}
	r = (double)ft_atoi(colors[0]) / 255;
	g = (double)ft_atoi(colors[1]) / 255;
	b = (double)ft_atoi(colors[2]) / 255;
	*color = init_color(r, g, b);
	free_strings(colors);
	return (PARSE_SUCCESS);
}

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
int	parse_vector(const char *str, t_vec3 *output)
{
	char	**coordinates;
	int		i;

	coordinates = ft_split(str, ',');
	if (count_strings(coordinates) != 3)
		return (handle_parse_error(coordinates));
	i = 0;
	while (coordinates[i])
	{
		if (!is_floating_point(coordinates[i]))
			return (handle_parse_error(coordinates));
		i++;
	}
	output->x = ft_atof(coordinates[0]);
	output->y = ft_atof(coordinates[1]);
	output->z = ft_atof(coordinates[2]);
	free_strings(coordinates);
	return (PARSE_SUCCESS);
}

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
int	parse_unit_vector(const char *str, t_vec3 *output)
{
	if (parse_vector(str, output) == PARSE_FAILED)
		return (PARSE_FAILED);
	if (ft_fabs(length_squared_vec3(*output) - 1.0) > EPSILON)
		return (PARSE_FAILED);
	return (PARSE_SUCCESS);
}

// typeが不明な場合もlambertianを返す
t_material	parse_material(const char *type, t_color albedo)
{
	if (ft_strcmp(type, "metal") == 0)
	{
		return (init_metal_material(albedo, 0));
	}
	if (ft_strcmp(type, "dielectric") == 0)
	{
		return (init_dielectric_material(1.5));
	}
	return (init_lambertian_material(albedo));
}
