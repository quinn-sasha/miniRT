#include "material.h"
#include "hit_record.h"
#include "random_number_generator.h"
#include "utils.h"
#include "vec3.h"
#include "math_utils.h"

t_material init_material(t_material_func p_func, t_color albedo, double fuzziness, double refract_idx)
{
    t_material material;
    material.scatters = p_func;
    material.albedo = albedo;
    material.fuzziness = fuzziness;
    material.refract_idx = refract_idx;
    return material;
}

t_material init_lambertian_material(t_color albedo, double fuzziness, double refract_idx)
{
    return init_material(lambertian_scatters, albedo, fuzziness, refract_idx);
}

t_material init_metal_material(t_color albedo, double fuzziness, double refract_idx)
{
    return init_material(metal_scatters, albedo, fuzziness, refract_idx);
}

t_material init_dielectric_material(t_color albedo, double fuzziness ,double refract_idx)
{
    return init_material(dielectric_scatters, albedo, fuzziness, refract_idx);
}

bool lambertian_scatters(t_ray ray, t_hit_record record, t_ray *scattered,
                        t_xorshift64_state *state)
{
    (void)ray;
    t_vec3 scatter_direction = add_vec3(record.normal_vector, get_random_unit_vec3(state));
    *scattered = init_ray(record.intersection, scatter_direction);
    return true;
}

bool metal_scatters(t_ray ray, t_hit_record record, t_ray *scattered,
                    t_xorshift64_state *state)
{
    t_vec3 reflected = reflect(normalize_vec3(ray.direction), record.normal_vector);
    t_vec3 direction = add_vec3(reflected, mult_scalar_vec3(get_random_vec3_in_unit_sphere(state),
                                record.material.fuzziness));
    *scattered = init_ray(record.intersection, direction);
    return (dot_vec3(scattered->direction, record.normal_vector) > 0);
}

bool dielectric_scatters(t_ray ray, t_hit_record record, t_ray *scattered,
                         t_xorshift64_state *state)
{
    (void)state;

    double refract_idx = record.material.refract_idx;
    double etai_over_etat;

    if (record.front_face)
        etai_over_etat = 1.0 / refract_idx; //空気1.0として計算
    else
        etai_over_etat = refract_idx; //内側は外部の屈折率を1.0としている

    t_vec3 unit_direciton = normalize_vec3(ray.direction);
    t_vec3 normal = record.normal_vector;
    double cos_theta = dot_vec3(negative_vec3(unit_direciton), normal);
    t_vec3 refracted = refract(unit_direciton, record.normal_vector, etai_over_etat); //レイの単位ベクトルを渡す
    //全反射
    if (length_squared_vec3(refracted) == 0.0)
    {
        t_vec3 reflected = reflect(unit_direciton, record.normal_vector);
        *scattered = init_ray(record.intersection, reflected);
    }
    else
    {
        double reflect_prob = schlick(cos_theta, etai_over_etat);
        //反射か屈折か（モンテカルロ法）
        if (random_double(state) < reflect_prob)
        {
            t_vec3 reflected = reflect(unit_direciton, normal);
            *scattered = init_ray(record.intersection, reflected);
        }
        else
            *scattered = init_ray(record.intersection, refracted);
    }
    return true;
}



//レイが散乱するか吸収されるかを判定する
//散乱するなら散乱レイと減衰を求める。
