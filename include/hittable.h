#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"

typedef struct s_hit_record {
  t_vec3 intersection;
  t_vec3 normal_vector;
  double t; // ray parameter
} t_hit_record;

#endif
