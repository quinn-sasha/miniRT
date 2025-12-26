/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 20:26:19 by ikota             #+#    #+#             */
/*   Updated: 2025/12/27 01:10:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
#define CYLINDER_H

#include "material.h"
#include "range.h"
#include "vec3.h"
#include <stdbool.h>

typedef struct s_cylinder {
  t_vec3 center;
  t_vec3 axis;
  double radius;
  double height;
  t_material material;
} t_cylinder;

typedef struct s_basis {
  t_vec3 ex;
  t_vec3 ey;
  t_vec3 ez;
} t_basis;

t_cylinder *new_cylinder(t_vec3 *vectors, double *dimensions,
                         t_material material);

bool hit_cylinder(const t_ray ray, t_range range, t_hit_record *hit_rec,
                  const t_cylinder *cyl);

#endif
