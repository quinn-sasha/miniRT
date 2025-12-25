#include "vec3.h"
#include <math.h>

t_vec3 reflect(t_vec3 incoming, t_vec3 normal) {
  double temp = dot_vec3(incoming, normal);
  return add_vec3(incoming, scale_vec3(normal, -2 * temp));
}

t_vec3 refract(t_vec3 incoming, t_vec3 n, double eta_in_over_etat) {
  double cos_theta = -dot_vec3(incoming, n);
  t_vec3 parallel = scale_vec3(add_vec3(incoming, scale_vec3(n, cos_theta)),
                               eta_in_over_etat);
  double scalar = -sqrt(1.0 - length_squared_vec3(parallel));
  t_vec3 perpendicular = scale_vec3(n, scalar);
  return add_vec3(parallel, perpendicular);
}
