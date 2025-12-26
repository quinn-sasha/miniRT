/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 20:00:38 by squinn            #+#    #+#             */
/*   Updated: 2025/12/25 20:00:39 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_utils.h"
#include "libft.h"
#include "parse.h"
#include "parse_utils.h"
#include "utilities.h"

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
static int	parse_plane_helper(const char *line, t_program *data)
{
	char		**params;
	t_vec3		point;
	t_vec3		normal;
	t_color		albedo;
	t_material	material;

	params = ft_split(line, ' ');
	if (count_strings(params) != 5)
		return (handle_parse_error(params));
	if (parse_vector(params[1], &point) == PARSE_FAILED)
		return (handle_parse_error(params));
	if (parse_unit_vector(params[2], &normal) == PARSE_FAILED)
		return (handle_parse_error(params));
	if (parse_color(params[3], &albedo) == PARSE_FAILED)
		return (handle_parse_error(params));
	material = parse_material(params[4], albedo);
	add_plane(&data->head, new_plane(point, normal, material));
	free_strings(params);
	return (PARSE_SUCCESS);
}

int	parse_plane(const char *line, t_program *data)
{
	if (parse_plane_helper(line, data) == PARSE_FAILED)
		return (error_return("Invalid plane setting", PARSE_FAILED));
	return (PARSE_SUCCESS);
}
