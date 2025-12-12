#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"
#include "random_number_generator.h"
#include "ray.h"
#include <stdbool.h>

typedef struct s_hit_record t_hit_record;

typedef bool (*t_material_func)(t_ray ray, t_hit_record record,
                                t_ray *scatterred, t_xorshift64_state *state);

typedef enum {
    MATERIAL_LAMBERTHIAN,
    MATERIAL_METAL,
} e_material_type;

typedef struct s_material
{
    t_material_func scatters;
    t_color albedo; //albedo = attenuation
    double  fuzziness; //ぼやけ　反射したレイをランダムに変化させる
} t_material;

bool lambertian_scatters(t_ray ray, t_hit_record record, t_ray *scattered,
                    t_xorshift64_state *state);

bool metal_scatters(t_ray ray, t_hit_record record, t_ray *scattered,
                    t_xorshift64_state *state);

t_material init_material(t_material_func p_func, t_color albedo, double fuzziness);

t_material init_lambertian_material(t_color albedo, double fuzziness);
t_material init_metal_material(t_color albedom, double fuzziness);

#endif
