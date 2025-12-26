#include "color.h"
#include "hit_record.h"
#include "light.h"
#include "minirt.h"
#include "object_list.h"
#include "vec3.h"
#include <math.h>

t_color calculate_color(t_ray ray, t_program *data, t_xorshift64_state *state,
                        int num_recursions);

static t_vec3 calculate_diffuse(t_light *light, t_hit_record *record,
                                t_vec3 normalized_light_dir_vec) {
  double dot_nl;
  t_color diffuse_light;
  t_color diffuse;

  dot_nl = dot_vec3(record->normal_vector, normalized_light_dir_vec);
  if (dot_nl < 0)
    dot_nl = 0;
  diffuse_light = scale_vec3(light->color, light->brightness_ratio * dot_nl);
  diffuse = multiply_vec3(diffuse_light, record->material.albedo);
  return (diffuse);
}

static t_vec3 calculate_specular(t_hit_record *record, t_light *light,
                                 t_ray ray, t_vec3 normalized_light_dir_vec) {
  t_vec3 reflected;
  t_vec3 negative_ray_dir;
  double dot_rn;
  double shininess;
  t_color specular_color;
  double specular_factor;

  reflected =
      reflect(negative_vec3(normalized_light_dir_vec), record->normal_vector);
  negative_ray_dir = negative_vec3(ray.direction);
  dot_rn = dot_vec3(reflected, negative_ray_dir);
  if (dot_rn < 0)
    return (init_color(0, 0, 0));
  shininess = 32;
  specular_color = multiply_vec3(light->color, record->material.albedo);
  specular_factor = pow(dot_rn, shininess);
  return (
      scale_vec3(specular_color, light->brightness_ratio * specular_factor));
}

t_color calculate_direct_lighting(t_hit_record *record, t_scene_object *head,
                                  t_light *light, t_ray ray) {
  t_vec3 light_dir_vec;
  double distance_to_light;
  t_vec3 normalized_light_dir_vec;
  t_ray shadow_ray;
  t_hit_record shadow_rec;
  t_color diffuse;
  t_color specular;

  light_dir_vec = sub_vec3(light->pos, record->intersection);
  distance_to_light = length_vec3(light_dir_vec);
  normalized_light_dir_vec = normalize_vec3(light_dir_vec);
  shadow_ray = init_ray(record->intersection, normalized_light_dir_vec);
  if (hits_any_object(head, shadow_ray, 0.001, distance_to_light, &shadow_rec))
    return (init_color(0, 0, 0));
  diffuse = calculate_diffuse(light, record, normalized_light_dir_vec);
  specular = init_color(0, 0, 0);
  if (record->material.type == MAT_METAL)
    specular = calculate_specular(record, light, ray, normalized_light_dir_vec);
  return (add_vec3(diffuse, specular));
}

t_color calculate_indirect_lighting(t_hit_record record,
                                    t_xorshift64_state *state, t_ray ray,
                                    int num_recursions, t_program *data) {
  t_ray scattered;
  t_color attenuation;
  t_color indirect_light;
  bool can_scatter;
  t_color recursive_color;

  attenuation = record.material.albedo;
  indirect_light = init_color(0, 0, 0);
  can_scatter = false;
  if (record.material.type == MAT_LAMBERTIAN)
    can_scatter = lambertian_scatters(record, &scattered, state);
  else if (record.material.type == MAT_METAL)
    can_scatter = metal_scatters(ray, record, &scattered, state);
  else if (record.material.type == MAT_DIELECTRIC) {
    can_scatter = dielectric_scatters(ray, record, &scattered, state);
    attenuation = init_color(1.0, 1.0, 1.0);
  }
  if (can_scatter) {
    recursive_color =
        calculate_color(scattered, data, state, num_recursions - 1);
    indirect_light = multiply_vec3(recursive_color, attenuation);
  }
  return (indirect_light);
}

t_color calculate_background_color(t_ray ray) {
  double t;
  t_color white;

  t = 0.5 * (ray.direction.y + 1.0);
  white = init_color(1.0, 1.0, 1.0);
  return (add_vec3(scale_vec3(white, (1.0 - t)),
                   scale_vec3(init_color(0.5, 0.7, 1.0), t)));
}
