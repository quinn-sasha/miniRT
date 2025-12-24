#include "math_utils.h"
#include <math.h>

double degrees_to_radians(double degrees) { return (degrees * (M_PI / 180.0)); }

double solve_quadratic_t(double a, double half_b, double c, double min_t,
                       double max_t) {
  double discriminant = half_b * half_b - a * c;
  if (discriminant < 0.0)
    return false;
  double root = sqrt(discriminant);
  double smaller_t = (-half_b - root) / a;
  double bigger_t = (-half_b + root) / a;

  double t;
  if (smaller_t < max_t && smaller_t > min_t)
    t = smaller_t;
  else if (bigger_t > min_t && bigger_t < max_t)
    t = bigger_t;
  else
    return false;
  return t;
}
