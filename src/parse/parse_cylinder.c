/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 19:44:39 by squinn            #+#    #+#             */
/*   Updated: 2025/12/25 19:51:11 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "error_utils.h"
#include "libft.h"
#include "parse.h"
#include "parse_utils.h"
#include "utilities.h"
#include <math.h>

static int parse_attrs(char **params, t_vec3 *vectors, double *dimensions) {
  if (parse_vector(params[1], &vectors[0]) == PARSE_FAILED)
    return (PARSE_FAILED);
  if (parse_unit_vector(params[2], &vectors[1]) == PARSE_FAILED)
    return (PARSE_FAILED);
  if (parse_double_range(params[3], &dimensions[0], 0, INFINITY) ==
      PARSE_FAILED)
    return (PARSE_FAILED);
  if (parse_double_range(params[4], &dimensions[1], 0, INFINITY) ==
      PARSE_FAILED)
    return (PARSE_FAILED);
  return (PARSE_SUCCESS);
}

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
static int parse_cylinder_helper(const char *line, t_program *data) {
  char **params;
  t_vec3 vectors[2];
  double dimensions[2];
  t_color albedo;
  t_cylinder *cylinder;

  params = ft_split(line, ' ');
  if (count_strings(params) != 7)
    return (handle_parse_error(params));
  if (parse_attrs(params, vectors, dimensions) == PARSE_FAILED)
    return (handle_parse_error(params));
  if (parse_color(params[5], &albedo) == PARSE_FAILED)
    return (handle_parse_error(params));
  cylinder =
      new_cylinder(vectors, dimensions, parse_material(params[6], albedo));
  add_cylinder(&data->head, cylinder);
  free_strings(params);
  return (PARSE_SUCCESS);
}

int parse_cylinder(const char *line, t_program *data) {
  if (parse_cylinder_helper(line, data) == PARSE_FAILED)
    return (error_return("Invalid cylinder setting", PARSE_FAILED));
  return (PARSE_SUCCESS);
}
