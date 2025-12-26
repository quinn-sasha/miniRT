/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 20:00:04 by squinn            #+#    #+#             */
/*   Updated: 2025/12/25 20:00:05 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "error_utils.h"
#include "libft.h"
#include "minirt.h"
#include "parse.h"
#include "parse_line.h"

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
int	parse_line(const char *line, t_elements_count *counts, t_program *data)
{
	if (*line == '\0' || *line == '\n' || *line == '#')
		return (PARSE_SUCCESS);
	if (ft_strncmp(line, "A ", 2) == 0)
		return (parse_ambient(line, counts, data));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_camera(line, counts, data));
	if (ft_strncmp(line, "L ", 2) == 0)
		return (parse_light(line, counts, data));
	if (ft_strncmp(line, "sp ", 3) == 0)
		return (parse_sphere(line, data));
	if (ft_strncmp(line, "pl ", 3) == 0)
		return (parse_plane(line, data));
	if (ft_strncmp(line, "cy ", 3) == 0)
		return (parse_cylinder(line, data));
	return (error_return("Unknown identifier", PARSE_FAILED));
}
