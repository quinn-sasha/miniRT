#include "material.h"
#include "hit_record.h"
#include "random_number_generator.h"
#include "utils.h"
#include "vec3.h"

t_material init_material(t_material_func p_func, t_color albedo, double fuzziness, double ref_idx)
{
    t_material material;
    material.scatters = p_func;
    material.albedo = albedo;
    material.fuzziness = fuzziness;
    material.ref_idx = ref_idx;
    return material;
}

t_material init_lambertian_material(t_color albedo, double fuzziness, double ref_idx)
{
    return init_material(lambertian_scatters, albedo, fuzziness, ref_idx);
}

t_material init_metal_material(t_color albedo, double fuzziness, double ref_idx)
{
    return init_material(metal_scatters, albedo, fuzziness, ref_idx);
}

t_material init_dielectric_material(t_color albedo, double fuzziness ,double ref_idx)
{
    return init_material(dielectric_scatters, albedo, fuzziness, ref_idx);
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
    t_vec3 direction = vec3_add(reflected, vec3_mult_scalar(get_random_vec3_in_unit_sphere(state),
                                record.material.fuzziness));
    *scattered = init_ray(record.intersection, direction);
    return (vec3_dot(scattered->direction, record.normal_vector) > 0);
}

bool dielectric_scatters(t_ray ray, t_hit_record record, t_ray *scattered,
                         t_xorshift64_state *state)
{
    (void)state;

    double ref_idx = record.material.ref_idx;
    double etai_over_etat;

    if (record.front_face)
        etai_over_etat = 1.0 / ref_idx; //空気1.0として計算
    else
        etai_over_etat = ref_idx; //内側は外部の屈折率を1.0としている

    t_vec3 unit_direciton = vec3_unit_vector(ray.direction);
    t_vec3 refracted = refract(unit_direciton, record.normal_vector, etai_over_etat); //レイの単位ベクトルを渡す

    if (vec3_length_squared(refracted) == 0.0)
    {
        t_vec3 reflected = reflect(unit_direciton, record.normal_vector);
        *scattered = init_ray(record.intersection, reflected);
    }
    else
        *scattered = init_ray(record.intersection, refracted);
    return true;
}



//レイが散乱するか吸収されるかを判定する
//散乱するなら散乱レイと減衰を求める。
