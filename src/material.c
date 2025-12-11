#include "material.h"
#include "hit_record.h"
#include "random_number_generator.h"
#include "utils.h"
#include "vec3.h"

t_material init_material(t_material_func p_func, t_color albedo)
{
    t_material material;
    material.scatters = p_func;
    material.albedo = albedo;
    return material;
}

t_material init_lambertian_material(t_color albedo)
{
    return init_material(lambertian_scatters, albedo);
}

t_material init_metal_material(t_color albedo)
{
    return init_material(metal_scatters, albedo);
}

bool lambertian_scatters(t_ray ray, t_hit_record record, t_ray *scattered,
                        t_xorshift64_state *state)
{
    (void)ray;
    t_vec3 scatter_direction = vec3_add(record.normal_vector, get_random_unit_vec3(state));
    *scattered = init_ray(record.intersection, scatter_direction);
    return true;
}

bool metal_scatters(t_ray ray, t_hit_record record, t_ray *scattered,
                    t_xorshift64_state *state)
{
    t_vec3 reflected = reflect(vec3_unit_vector(ray.direction), record.normal_vector);
    // t_vec3 direction = vec3_add(reflected, vec3_scale(get_random_vec3_in_unit_sphere))
    *scattered = init_ray(record.intersection, reflected);
    return (vec3_dot(scattered->direction, record.normal_vector) > 0);
}

//レイが散乱するか吸収されるかを判定する
//散乱するなら散乱レイと減衰を求める。