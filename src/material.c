#include "material.h"
#include "hit_record.h"
#include "libft.h"
#include "random_number_generator.h"
#include "utilities.h"
#include "vec3.h"
#include <math.h>

static t_material init_material(t_color albedo) {
  t_material material;
  ft_memset(&material, 0, sizeof(t_material));
  material.albedo = albedo;
  return material;
}

t_material init_lambertian_material(t_color albedo) {
  t_material material = init_material(albedo);
  material.type = MAT_LAMBERTIAN;
  return material;
}

t_material init_metal_material(t_color albedo, double fuzziness) {
  t_material material = init_material(albedo);
  material.type = MAT_METAL;
  material.data.fuzziness = fuzziness;
  return material;
}

// Dielectric doesn't have albedo
t_material init_dielectric_material(double refractive_index) {
  t_material material;
  ft_memset(&material, 0, sizeof(t_material));
  material.type = MAT_DIELECTRIC;
  material.data.refractive_index = refractive_index;
  return material;
}

bool lambertian_scatters(t_hit_record record, t_ray *scattered,
                         t_xorshift64_state *state) {
  t_vec3 scatter_direction =
      add_vec3(record.normal_vector, init_random_unit_vec3(state));
  *scattered = init_ray(record.intersection, scatter_direction);
  return true;
}

bool metal_scatters(t_ray ray, t_hit_record record, t_ray *scattered,
                    t_xorshift64_state *state) {
  t_vec3 reflected =
      reflect(normalize_vec3(ray.direction), record.normal_vector);
  t_vec3 direction =
      add_vec3(reflected, scale_vec3(init_random_vec3_in_unit_shpere(state),
                                     record.material.data.fuzziness));
  *scattered = init_ray(record.intersection, direction);
  return (dot_vec3(reflected, record.normal_vector) > 0);
}

static double schlick_reflectivity(double eta_in_over_etat, double cos_theta) {
  double f0 = (1 - eta_in_over_etat) / (1 + eta_in_over_etat);
  f0 = f0 * f0;
  return f0 + (1 - f0) * pow(1 - cos_theta, 5);
}

bool dielectric_scatters(t_ray ray, t_hit_record record, t_ray *scattered,
                         t_color *attenuation, t_xorshift64_state *state) {
  const double refractive_index = record.material.data.refractive_index;
  *attenuation = init_color(1.0, 1.0, 1.0);
  double eta_in_over_etat;
  if (record.fronts_face) {
    eta_in_over_etat = 1.0 / refractive_index;
  } else {
    eta_in_over_etat = refractive_index;
  }

  t_vec3 incoming = normalize_vec3(ray.direction);
  double cos_theta =
      min_double(dot_vec3(inverse_vec3(incoming), record.normal_vector), 1.0);
  double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
  if (eta_in_over_etat * sin_theta > 1.0) {
    t_vec3 reflected = reflect(incoming, record.normal_vector);
    *scattered = init_ray(record.intersection, reflected);
    return true;
  }
  double reflectivity = schlick_reflectivity(eta_in_over_etat, cos_theta);
  if (reflectivity > random_double(state)) {
    t_vec3 reflected = reflect(incoming, record.normal_vector);
    *scattered = init_ray(record.intersection, reflected);
    return true;
  }
  t_vec3 refracted = refract(incoming, record.normal_vector, eta_in_over_etat);
  *scattered = init_ray(record.intersection, refracted);
  return true;
}
