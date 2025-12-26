/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 19:42:31 by squinn            #+#    #+#             */
/*   Updated: 2025/12/25 19:42:32 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_utils.h"
#include "libft.h"
#include "parse.h"
#include "parse_line.h"
#include "parse_utils.h"
#include "utilities.h"

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
static int	parse_ambient_helper(const char *line, t_elements_count *counts,
		t_program *data)
{
	char	**params;
	double	brightness;
	t_color	albedo;

	counts->num_ambient++;
	params = ft_split(line, ' ');
	if (count_strings(params) != 3)
		return (handle_parse_error(params));
	if (parse_clamped_double(params[1], &brightness, 0.0, 1.0) == PARSE_FAILED)
		return (handle_parse_error(params));
	if (parse_color(params[2], &albedo) == PARSE_FAILED)
		return (handle_parse_error(params));
	data->ambient = init_ambient(brightness, albedo);
	free_strings(params);
	return (PARSE_SUCCESS);
}

int	parse_ambient(const char *line, t_elements_count *counts, t_program *data)
{
	int	result;

	result = parse_ambient_helper(line, counts, data);
	if (result == PARSE_FAILED)
		return (error_return("Invalid ambient setting", PARSE_FAILED));
	return (PARSE_SUCCESS);
}
