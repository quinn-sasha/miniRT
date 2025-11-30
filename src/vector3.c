#include "minirt.h"

t_vector3 vec3_init(double x, double y, double z) {
  t_vector3 new;
  new.x = x;
  new.y = y;
  new.z = z;
  return new;
}

t_vector3 vec3_add(t_vector3 v1, t_vector3 v2) {
  return vec3_init(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

t_vector3 vec3_sub(t_vector3 v1, t_vector3 v2) {
  return vec3_init(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

t_vector3 vec3_scale(t_vector3 v, double scalar) {
  return vec3_init(v.x * scalar, v.y * scalar, v.z * scalar);
}

double vec3_dot(t_vector3 v1, t_vector3 v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

double vec3_length(t_vector3 v) {
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vector3 vec3_normalize(t_vector3 v) {
  double length = vec3_length(v);
  t_vector3 result = vec3_init(v.x / length, v.y / length, v.z / length);
  return result;
}
