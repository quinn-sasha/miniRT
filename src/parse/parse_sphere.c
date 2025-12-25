/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 20:01:01 by squinn            #+#    #+#             */
/*   Updated: 2025/12/25 20:01:02 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_utils.h"
#include "libft.h"
#include "parse.h"
#include "parse_utils.h"
#include "utilities.h"
#include <math.h>

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
static int	parse_sphere_helper(const char *line, t_program *data)
{
	char		**params;
	t_vec3		center;
	double		diameter;
	t_color		albedo;
	t_material	material;

	params = ft_split(line, ' ');
	if (count_strings(params) != 5)
		return (handle_parse_error(params));
	if (parse_vector(params[1], &center) == PARSE_FAILED)
		return (handle_parse_error(params));
	if (parse_double_range(params[2], &diameter, 0, INFINITY) == PARSE_FAILED)
		return (handle_parse_error(params));
	if (parse_color(params[3], &albedo) == PARSE_FAILED)
		return (handle_parse_error(params));
	material = parse_material(params[4], albedo);
	add_sphere(&data->head, new_sphere(center, diameter / 2, material));
	free_strings(params);
	return (PARSE_SUCCESS);
}

int	parse_sphere(const char *line, t_program *data)
{
	if (parse_sphere_helper(line, data) == PARSE_FAILED)
		return (error_return("Invalid sphere setting", PARSE_FAILED));
	return (PARSE_SUCCESS);
}
