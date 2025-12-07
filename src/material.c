#include "material.h"
#include "hit_record.h"
#include "random_number_generator.h"
#include "vec3.h"

bool lambertian_scatters(t_ray ray, t_hit_record record, t_ray *scattered,
                         t_xorshift64_state *state) {
  t_vec3 scatter_direction =
      vec3_add(record.normal_vector, get_random_unit_vec3(state));
  *scattered = init_ray(record.intersection, scatter_direction);
  return true;
}
