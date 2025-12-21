#include "vec3.h"
#include "random_number_generator.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

t_vec3 init_vec3(double x, double y, double z) {
  t_vec3 result;
  result.x = x;
  result.y = y;
  result.z = z;
  return result;
}

t_vec3 scale_vec3(t_vec3 v, double scalar) {
  return init_vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

t_vec3 divide_vec3(t_vec3 v, double scalar) {
  return scale_vec3(v, 1 / scalar);
}

t_vec3 negative_vec3(t_vec3 v) { return scale_vec3(v, -1); }

t_vec3 add_vec3(t_vec3 a, t_vec3 b) {
  return init_vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

t_vec3 add_triple_vec3(t_vec3 a, t_vec3 b, t_vec3 c) {
  return add_vec3(a, add_vec3(b, c));
}

t_vec3 sub_vec3(t_vec3 a, t_vec3 b) {
  return init_vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

double length_squared_vec3(t_vec3 v) {
  return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

double length_vec3(t_vec3 v) { return sqrt(length_squared_vec3(v)); }

double dot_vec3(t_vec3 a, t_vec3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec3 multiply_vec3(t_vec3 a, t_vec3 b) {
  return init_vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

t_vec3 normalize_vec3(t_vec3 v) {
  double length = length_vec3(v);
  return scale_vec3(v, 1 / length);
}

t_vec3 cross_vec3(t_vec3 a, t_vec3 b) {
  return init_vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
}

t_vec3 init_random_vec3(t_xorshift64_state *state) {
  double x = random_double(state);
  double y = random_double(state);
  double z = random_double(state);
  return init_vec3(x, y, z);
}

t_vec3 init_random_vec3_range(t_xorshift64_state *state, double min,
                              double max) {
  double x = random_double_range(state, min, max);
  double y = random_double_range(state, min, max);
  double z = random_double_range(state, min, max);
  return init_vec3(x, y, z);
}

t_vec3 init_random_vec3_in_unit_sphere(t_xorshift64_state *state) {
  while (true) {
    t_vec3 result = init_random_vec3_range(state, -1, 1);
    if (length_squared_vec3(result) >= 1)
      continue;
    return result;
  }
}

t_vec3 init_random_unit_vec3(t_xorshift64_state *state) {
  double a = random_double_range(state, 0, 2 * M_PI);
  double z = random_double_range(state, -1, 1);
  double small_r = sqrt(1 - z * z);
  return init_vec3(small_r * cos(a), small_r * sin(a), z);
}

t_vec3 init_random_vec3_in_unit_circle(t_xorshift64_state *state) {
  while (true) {
    double x = random_double_range(state, -1, 1);
    double y = random_double_range(state, -1, 1);
    t_vec3 result = init_vec3(x, y, 0);
    if (length_squared_vec3(result) >= 1)
      continue;
    return result;
  }
}

t_vec3 random_in_hemisphere(const t_vec3 normal, t_xorshift64_state *state) {
  t_vec3 in_unit_sphere = init_random_vec3_in_unit_sphere(state);
  if (dot_vec3(in_unit_sphere, normal) > 0.0)
    return (in_unit_sphere);
  else
    return negative_vec3(in_unit_sphere);
}

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
