#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <stdbool.h>

double degrees_to_radians(double degrees);
bool solve_quadratic_t(double a, double half_b, double c, double min_t,
                       double max_t, double *t);

#endif
