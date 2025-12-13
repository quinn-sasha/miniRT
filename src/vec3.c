#include "vec3.h"
#include "random_number_generator.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

t_vec3 vec3_init(double x, double y, double z) {
  t_vec3 result;
  result.x = x;
  result.y = y;
  result.z = z;
  return result;
}

t_vec3 vec3_scale(t_vec3 v, double scalar) {
  return vec3_init(v.x * scalar, v.y * scalar, v.z * scalar);
}

t_vec3 vec3_divide(t_vec3 v, double scalar) {
  return vec3_scale(v, 1 / scalar);
}

t_vec3 vec3_inverse(t_vec3 v) { return vec3_scale(v, -1); }

t_vec3 vec3_add(t_vec3 a, t_vec3 b) {
  return vec3_init(a.x + b.x, a.y + b.y, a.z + b.z);
}

t_vec3 vec3_add_triple(t_vec3 a, t_vec3 b, t_vec3 c) {
  return vec3_add(a, vec3_add(b, c));
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b) {
  return vec3_init(a.x - b.x, a.y - b.y, a.z - b.z);
}

double vec3_length_squared(t_vec3 v) {
  return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

double vec3_length(t_vec3 v) { return sqrt(vec3_length_squared(v)); }

double vec3_dot(t_vec3 a, t_vec3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec3 vec3_multiply(t_vec3 a, t_vec3 b) {
  return vec3_init(a.x * b.x, a.y * b.y, a.z * b.z);
}

t_vec3 vec3_normalize(t_vec3 v) {
  double length = vec3_length(v);
  return vec3_scale(v, 1 / length);
}

void vec3_print(t_vec3 v) { printf("x: %e, y: %e, z: %e\n", v.x, v.y, v.z); }

t_vec3 vec3_cross(t_vec3 a, t_vec3 b) {
  return vec3_init(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
}

t_vec3 init_random_vec3(t_xorshift64_state *state) {
  double x = random_double(state);
  double y = random_double(state);
  double z = random_double(state);
  return vec3_init(x, y, z);
}

t_vec3 init_random_vec3_range(t_xorshift64_state *state, double min,
                              double max) {
  double x = random_double_range(state, min, max);
  double y = random_double_range(state, min, max);
  double z = random_double_range(state, min, max);
  return vec3_init(x, y, z);
}

t_vec3 get_random_vec3_in_unit_shpere(t_xorshift64_state *state) {
  while (true) {
    t_vec3 result = init_random_vec3_range(state, -1, 1);
    if (vec3_length_squared(result) >= 1)
      continue;
    return result;
  }
}

t_vec3 get_random_unit_vec3(t_xorshift64_state *state) {
  double a = random_double_range(state, 0, 2 * M_PI);
  double z = random_double_range(state, -1, 1);
  double small_r = sqrt(1 - z * z);
  return vec3_init(small_r * cos(a), small_r * sin(a), z);
}

t_vec3 get_random_vec3_in_unit_circle(t_xorshift64_state *state) {
  while (true) {
    double x = random_double_range(state, -1, 1);
    double y = random_double_range(state, -1, 1);
    t_vec3 result = vec3_init(x, y, 0);
    if (vec3_length_squared(result) >= 1)
      continue;
    return result;
  }
}

t_vec3 get_diffuse_vector_from_intersection(t_vec3 intersection,
                                            t_vec3 normal_vector,
                                            t_xorshift64_state *state) {
  return vec3_add_triple(intersection, normal_vector,
                         get_random_unit_vec3(state));
}

t_vec3 reflect(t_vec3 incoming, t_vec3 normal) {
  double temp = vec3_dot(incoming, normal);
  return vec3_add(incoming, vec3_scale(normal, -2 * temp));
}

t_vec3 refract(t_vec3 incoming, t_vec3 n, double eta_in_over_etat) {
  double cos_theta = -vec3_dot(incoming, n);
  t_vec3 parallel = vec3_scale(vec3_add(incoming, vec3_scale(n, cos_theta)),
                               eta_in_over_etat);
  double scalar = -sqrt(1.0 - vec3_length_squared(parallel));
  t_vec3 perpendicular = vec3_scale(n, scalar);
  return vec3_add(parallel, perpendicular);
}
