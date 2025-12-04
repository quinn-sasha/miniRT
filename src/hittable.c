#include "hittable.h"

void set_fronts_face_and_normal_vector(t_hit_record *record, t_ray ray,
                                       t_vec3 outward_normal_vector) {
  if (vec3_dot(ray.direction, outward_normal_vector) > 0.0) {
    record->fronts_face = false;
    record->normal_vector = vec3_scale(outward_normal_vector, -1);
    return;
  }
  record->fronts_face = true;
  record->normal_vector = outward_normal_vector;
}
