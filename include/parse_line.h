/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 20:03:31 by squinn            #+#    #+#             */
/*   Updated: 2025/12/25 20:03:32 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_LINE_H
# define PARSE_LINE_H

# include "minirt.h"
# include "parse.h"

int	parse_ambient(const char *line, t_elements_count *counts, t_program *data);
int	parse_light(const char *line, t_elements_count *counts, t_program *data);
int	parse_camera(const char *line, t_elements_count *counts, t_program *data);
int	parse_sphere(const char *line, t_program *data);
int	parse_plane(const char *line, t_program *data);
int	parse_cylinder(const char *line, t_program *data);
int	parse_line(const char *line, t_elements_count *counts, t_program *data);

#endif
