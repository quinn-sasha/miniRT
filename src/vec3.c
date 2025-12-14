#include "vec3.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
//ベクトルを生成
t_vec3 init_vec3(double x, double y, double z)
{
    t_vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return (v);
}

t_vec3 add_vec3(t_vec3 u, t_vec3 v)
{
    return init_vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

t_vec3 add_triple_vec3(t_vec3 a, t_vec3 b, t_vec3 c) {
  return add_vec3(a, add_vec3(b, c));
}

t_vec3 sub_vec3(t_vec3 u, t_vec3 v)
{
    return init_vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}
//乗算
t_vec3 mult_vec3(t_vec3 u, t_vec3 v)
{
    return init_vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}
//ベクトルの長さを変える　乗算
t_vec3 mult_scalar_vec3(t_vec3 v, double t)
{
    return init_vec3(v.x * t, v.y * t, v.z * t);
}

t_vec3 div_scalar_vec3(t_vec3 v, double t)
{
    return mult_scalar_vec3(v, 1.0 / t);
}
//符号反転（負ベクトル）
t_vec3 negative_vec3(t_vec3 v)
{
    return init_vec3(-v.x, -v.y, -v.z);
}
//長さの二乗
double length_squared_vec3(t_vec3 v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}
//長さ
double length_vec3(t_vec3 v)
{
    return sqrt(length_squared_vec3(v));
}
//内積
double dot_vec3(t_vec3 u, t_vec3 v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}
//外積
t_vec3 cross_vec3(t_vec3 u, t_vec3 v)
{
    return init_vec3(u.y * v.z - u.z * v.y,
                    u.z * v.x - u.x * v.z,
                    u.x * v.y - u.y * v.x);
}

//単位ベクトル
t_vec3 normalize_vec3(t_vec3 v)
{
    return div_scalar_vec3(v, length_vec3(v));
}

t_vec3 init_random_vec3(t_xorshift64_state *state)
{
    double x = random_double(state);
    double y = random_double(state);
    double z = random_double(state);
    return init_vec3(x, y, z);
}

t_vec3 init_random_vec3_range(t_xorshift64_state *state, double min, double max)
{
    double x = random_double_range(state, min, max);
    double y = random_double_range(state, min, max);
    double z = random_double_range(state, min, max);
    return init_vec3(x, y, z);
}

t_vec3 get_random_vec3_in_unit_sphere(t_xorshift64_state *state)
{
    while (true)
    {
        t_vec3 result = init_random_vec3_range(state, -1, 1);
        if (length_squared_vec3(result) >= 1)
            continue; //ループの最初の処理に戻る
        return (result);
    }
}

t_vec3 get_random_unit_vec3(t_xorshift64_state *state)
{
    double a = random_double_range(state, 0, 2 * M_PI);
    double z = random_double_range(state, -1, 1);
    double small_r = sqrt(1 - z * z);
    return init_vec3(small_r * cos(a), small_r * sin(a), z);
}

t_vec3  random_in_hemisphere(const t_vec3 normal, t_xorshift64_state *state)
{
    t_vec3 in_unit_sphere = get_random_vec3_in_unit_sphere(state);
    if (dot_vec3(in_unit_sphere, normal) > 0.0)
        return (in_unit_sphere);
    else
        return negative_vec3(in_unit_sphere);
}

t_vec3 get_random_vec3_in_unit_circle(t_xorshift64_state *state)
{
    while (true)
    {
        double x = random_double_range(state, -1, 1);
        double y = random_double_range(state, -1, 1);
        t_vec3 result = init_vec3(x, y, 0);
        if (length_squared_vec3(result) >= 1)
            continue; //x^2 + y^2 = < 1.0 を満たす
        return (result);
    }
}

t_vec3 reflect(t_vec3 incoming, t_vec3 normal)
{
    double temp = dot_vec3(incoming, normal);
    return add_vec3(incoming, mult_scalar_vec3(normal, -2 * temp));
}

t_vec3 refract(t_vec3 incoming, t_vec3 normal, double etai_over_etat)
{
    double cos_theta = dot_vec3(negative_vec3(incoming), normal);

    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    if (etai_over_etat * sin_theta > 1.0)
        return init_vec3(0, 0, 0);

    //屈折レイの並行成分の計算
    t_vec3 temp = add_vec3(incoming, mult_scalar_vec3(normal, cos_theta));
    t_vec3 refract_parallel = mult_scalar_vec3(temp ,etai_over_etat);

    //屈折レイの垂直成分の計算
    //  vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared()) * n;
    double refract_parallel_squared = length_squared_vec3(refract_parallel);
    t_vec3 refract_perp = mult_scalar_vec3(normal ,-sqrt(1.0 - refract_parallel_squared));

    return add_vec3(refract_parallel, refract_perp);
}
