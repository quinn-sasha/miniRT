#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "range.h"
#include "sphere.h"
#include "cylinder.h"
#include <stdbool.h>

typedef struct s_quadratic {
  double a;
  double half_b;
  double c;
  double discriminant;
} t_quadratic;

double degrees_to_radians(double degrees);
t_quadratic prepare_quadratic_sphere(t_ray ray, t_sphere sphere);
t_quadratic prepare_quadratic_cylinder(t_ray ray, const t_cylinder *cyl);
double solve_quadratic_t(t_quadratic quadratic, t_range range);

#endif
