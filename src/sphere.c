#include "sphere.h"
#include "hit_record.h"
#include <math.h>
#include <stdlib.h>

// TODO: malloc error handling
t_sphere *new_sphere(t_vec3 center, double radius) {
  t_sphere *new_sphere = malloc(sizeof(t_sphere));
  new_sphere->center = center;
  new_sphere->radius = radius;
  return new_sphere;
}

bool hits_sphere(t_ray ray, double min_t, double max_t,
                 t_hit_record *hit_record, t_sphere sphere) {
  t_vec3 sphere2camera = vec3_sub(ray.origin, sphere.center);
  double a = vec3_length_squared(ray.direction);
  double half_b = vec3_dot(sphere2camera, ray.direction);
  double c = vec3_length_squared(sphere2camera) - sphere.radius * sphere.radius;
  double discriminant = half_b * half_b - a * c;
  if (discriminant < 0)
    return false;
  double smaller_t = (-half_b - sqrt(discriminant)) / a;
  double bigger_t = (-half_b + sqrt(discriminant)) / a;
  double t;
  if (smaller_t > min_t && smaller_t < max_t)
    t = smaller_t;
  else if (bigger_t > min_t && bigger_t < max_t)
    t = bigger_t;
  else
    return false;
  hit_record->t = t;
  hit_record->intersection = ray_at(ray, t);
  t_vec3 outward_normal_vector = vec3_divide(
      vec3_sub(hit_record->intersection, sphere.center), sphere.radius);
  set_fronts_face_and_normal_vector(hit_record, ray, outward_normal_vector);
  return true;
}
