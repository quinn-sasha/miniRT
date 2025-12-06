#ifndef SPHERE_H
#define SPHERE_H

#include "hit_record.h"
#include "ray.h"
#include "vec3.h"
#include <stdbool.h>

typedef struct s_sphere {
  t_vec3 center;
  double radius;
} t_sphere;

t_sphere *new_sphere(t_vec3 center, double radius);
bool hits_sphere(t_ray ray, double min_t, double max_t,
                 t_hit_record *hit_record, t_sphere sphere);

#endif // !SPHERE_H
