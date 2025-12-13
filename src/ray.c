#include "ray.h"

t_ray init_ray(t_vec3 origin, t_vec3 direction) {
  t_ray new_ray;
  new_ray.origin = origin;
  new_ray.direction = direction;
  return new_ray;
}

t_vec3 ray_at(t_ray ray, double t) {
  return add_vec3(ray.origin, scale_vec3(ray.direction, t));
}
