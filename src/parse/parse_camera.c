/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 19:43:08 by squinn            #+#    #+#             */
/*   Updated: 2025/12/25 19:43:09 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_utils.h"
#include "libft.h"
#include "parse.h"
#include "parse_utils.h"
#include "utilities.h"

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
static int	parse_camera_helper(const char *line, t_elements_count *counts,
		t_program *data)
{
	char	**params;
	t_vec3	lookfrom;
	t_vec3	direction;
	double	hfov;

	counts->num_cameras++;
	params = ft_split(line, ' ');
	if (count_strings(params) != 4)
		return (handle_parse_error(params));
	if (parse_vector(params[1], &lookfrom) == PARSE_FAILED)
		return (handle_parse_error(params));
	if (parse_unit_vector(params[2], &direction) == PARSE_FAILED)
		return (handle_parse_error(params));
	if (parse_double_range(params[3], &hfov, 0, 180) == PARSE_FAILED)
		return (handle_parse_error(params));
	setup_camera(lookfrom, direction, hfov, data);
	free_strings(params);
	return (PARSE_SUCCESS);
}

int	parse_camera(const char *line, t_elements_count *counts, t_program *data)
{
	if (parse_camera_helper(line, counts, data) == PARSE_FAILED)
		return (error_return("Invalid camera setting", PARSE_FAILED));
	return (PARSE_SUCCESS);
}
