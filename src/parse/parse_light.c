/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 19:59:33 by squinn            #+#    #+#             */
/*   Updated: 2025/12/25 19:59:34 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_utils.h"
#include "libft.h"
#include "parse.h"
#include "parse_utils.h"
#include "utilities.h"

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
static int	parse_light_helper(const char *line, t_elements_count *counts,
		t_program *data)
{
	char	**params;
	t_vec3	pos;
	double	brightness;
	t_color	color;

	counts->num_lights++;
	params = ft_split(line, ' ');
	if (count_strings(params) != 4)
		return (handle_parse_error(params));
	if (parse_vector(params[1], &pos) == PARSE_FAILED)
		return (handle_parse_error(params));
	if (parse_clamped_double(params[2], &brightness, 0.0, 1.0) == PARSE_FAILED)
		return (handle_parse_error(params));
	if (parse_color(params[3], &color) == PARSE_FAILED)
		return (handle_parse_error(params));
	data->light = init_light(pos, brightness, color);
	free_strings(params);
	return (PARSE_SUCCESS);
}

int	parse_light(const char *line, t_elements_count *counts, t_program *data)
{
	if (parse_light_helper(line, counts, data) == PARSE_FAILED)
		return (error_return("Invalid light setting", PARSE_FAILED));
	return (PARSE_SUCCESS);
}
