#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "material.h"
#include "ray.h"
#include "vec3.h"
#include <stdbool.h>

typedef struct s_hit_record t_hit_record;

struct s_hit_record {
  t_vec3 intersection;
  t_vec3 normal_vector;
  double t; // ray parameter
  bool fronts_face;
  t_material material;
};

void set_fronts_face_and_normal_vector(t_hit_record *record, t_ray ray,
                                       t_vec3 outward_normal_vector);

#endif
