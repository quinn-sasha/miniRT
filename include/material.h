#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "ray.h"
#include <stdbool.h>

typedef struct s_hit_record t_hit_record;

typedef bool (*t_material_func)(t_ray ray, t_hit_record record,
                                t_ray *scattered);

typedef enum {
  MATERIAL_LAMBERTIAN,
  MATERIAL_METAL,
} e_material_type;

typedef struct s_material {
  t_material_func scatters;
  t_color albedo; // albedo = attenuation
} t_material;

bool lambertian_scatters(t_ray ray, t_hit_record record, t_ray *scattered,
                         t_xorshift64_state *state);

#endif // !MATERIAL_H
