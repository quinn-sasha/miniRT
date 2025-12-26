/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 20:26:19 by ikota             #+#    #+#             */
/*   Updated: 2025/12/26 13:55:58 by ikota            ###   ########.fr       */
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

t_cylinder *new_cylinder(t_vec3 center, t_vec3 axis, double radius,
                         double height, t_material material);

bool hit_cylinder(const t_ray ray, t_range range, t_hit_record *hit_rec,
                  const t_cylinder *cyl);

#endif
