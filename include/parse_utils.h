/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 20:03:56 by squinn            #+#    #+#             */
/*   Updated: 2025/12/25 20:03:57 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include "material.h"
# include "vec3.h"

// parse_double.c
int			parse_double(const char *str, double *result);
int			parse_double_range(const char *str, double *result, double min,
				double max);
int			parse_clamped_double(const char *str, double *result, double min,
				double max);
// parse_utils.c
int			parse_color(const char *str, t_color *color);
int			parse_vector(const char *str, t_vec3 *output);
int			parse_unit_vector(const char *str, t_vec3 *output);
t_material	parse_material(const char *type, t_color albedo);

#endif // !PARSE_UTILS_H
