#include "vec3.h"
#include <stdio.h>
//ベクトルを生成
t_vec3 vec3_new(double x, double y, double z)
{
    t_vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return (v);
}
//ゼロベクトル生成
t_vec3 vec3_zero(void)
{
    t_vec3 v;
    v.x = 0.0;
    v.y = 0.0;
    v.z = 0.0;
    return (v);
}

t_vec3 vec3_add(t_vec3 u, t_vec3 v)
{
    return vec3_new(u.x + v.x, u.y + v.y, u.z + v.z);
}

t_vec3 vec3_sub(t_vec3 u, t_vec3 v)
{
    return vec3_new(u.x - v.x, u.y - v.y, u.z - v.z);
}
//乗算
t_vec3 vec3_mult(t_vec3 u, t_vec3 v)
{
    return vec3_new(u.x * v.x, u.y * v.y, u.z * v.z);
}
//ベクトルの長さを変える　乗算
t_vec3 vec3_mult_scalar(t_vec3 v, double t)
{
    return vec3_new(v.x * t, v.y * t, v.z * t);
}

t_vec3 vec3_div_scalar(t_vec3 v, double t)
{
    return vec3_mult_scalar(v, 1.0 / t);
}
//符号反転（負ベクトル）
t_vec3 vec3_neg(t_vec3 v)
{
    return vec3_new(-v.x, -v.y, -v.z);
}
//長さの二乗
double vec3_length_squared(t_vec3 v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}
//長さ
double vec3_length(t_vec3 v)
{
    return sqrt(vec3_length_squared(v));
}
//内積
double vec3_dot(t_vec3 u, t_vec3 v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}
//外積
t_vec3 vec3_cross(t_vec3 u, t_vec3 v)
{
    return vec3_new(u.y * v.z - u.z * v.y,
                    u.z * v.x - u.x * v.z,
                    u.x * v.y - u.y * v.x);
}

//単位ベクトル
t_vec3 vec3_unit_vector(t_vec3 v)
{
    return vec3_div_scalar(v, vec3_length(v));
}
