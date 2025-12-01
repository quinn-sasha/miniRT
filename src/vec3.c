#include "vec3.h"
#include <math.h>
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

t_vec3 vec3_add(t_vec3 a, t_vec3 b) {
  return vec3_init(a.x + b.x, a.y + b.y, a.z + b.z);
}

t_vec3 vec3_subtract(t_vec3 a, t_vec3 b) {
  return vec3_init(a.x - b.x, a.y - b.y, a.z - b.z);
}

double vec3_length(t_vec3 v) {
  return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

double vec3_dot(t_vec3 a, t_vec3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
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
