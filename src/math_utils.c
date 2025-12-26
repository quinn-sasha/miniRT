#include "math_utils.h"
#include "range.h"
#include "sphere.h"
#include "cylinder.h"
#include "ray.h"
#include <math.h>

double degrees_to_radians(double degrees)
{
  return (degrees * (M_PI / 180.0));
}

t_quadratic prepare_quadratic_sphere(t_ray ray, t_sphere sphere)
{
  t_quadratic q;
  t_vec3 sphere2camera;

  sphere2camera = sub_vec3(ray.origin, sphere.center);
  q.a = length_squared_vec3(ray.direction);
	q.half_b = dot_vec3(sphere2camera, ray.direction);
	q.c = length_squared_vec3(sphere2camera) - sphere.radius * sphere.radius;
  q.discriminant = q.half_b * q.half_b - q.a * q.c;
  return q;
}

t_quadratic prepare_quadratic_cylinder(t_ray ray, const t_cylinder *cyl)
{
  t_quadratic q;
  t_vec3 cylinder2camera;

  cylinder2camera = sub_vec3(ray.origin, cyl->center);
  q.a = length_squared_vec3(ray.direction);
	q.half_b = dot_vec3(cylinder2camera, ray.direction);
	q.c = length_squared_vec3(cylinder2camera) - cyl->radius * cyl->radius;
  q.discriminant = q.half_b * q.half_b - q.a * q.c;
  return q;
}

double solve_quadratic_t(t_quadratic quadratic, t_range range)
{
  if (quadratic.discriminant < 0.0)
    return false;
  double root = sqrt(quadratic.discriminant);
  double smaller_t = (-quadratic.half_b - root) / quadratic.a;
  double bigger_t = (-quadratic.half_b + root) / quadratic.a;

  double t;
  if (smaller_t < range.max_t && smaller_t > range.min_t)
    t = smaller_t;
  else if (bigger_t > range.min_t && bigger_t < range.max_t)
    t = bigger_t;
  else
    return false;
  return t;
}
