#include "sphere.h"
#include "hit_record.h"
#include "vec3.h"
#include "cylinder.h"
#include "math_utils.h"
#include <math.h>
#include <stdlib.h>

// TODO: malloc error handling
t_sphere *new_sphere(t_vec3 center, double radius, t_material material) {
  t_sphere *new_sphere = malloc(sizeof(t_sphere));
  new_sphere->center = center;
  new_sphere->radius = radius;
  new_sphere->material = material;
  return new_sphere;
}

bool hits_sphere(t_ray ray, double min_t, double max_t,
                 t_hit_record *record, t_sphere sphere) {
  t_vec3 sphere2camera = sub_vec3(ray.origin, sphere.center);
  double a = length_squared_vec3(ray.direction);
  double half_b = dot_vec3(sphere2camera, ray.direction);
  double c = length_squared_vec3(sphere2camera) - sphere.radius * sphere.radius;

  record->t = solve_quadratic_t(a, half_b, c, min_t, max_t);

  if (record->t == false)
    return false;

  record->intersection = ray_at(ray, record->t);
  t_vec3 outward_normal_vector = divide_vec3(
      sub_vec3(record->intersection, sphere.center), sphere.radius);
  set_fronts_face_and_normal_vector(record, ray, outward_normal_vector);
  record->material = sphere.material;
  return true;
}
