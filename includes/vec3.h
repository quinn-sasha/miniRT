#ifndef VEC3_H
# define  VEC3_H

#include <math.h>
#include <stdbool.h>
#include "random_number_generator.h"

typedef struct s_vec3
{
    double x;
    double y;
    double z;
} t_vec3;

typedef t_vec3 t_point3;
typedef t_vec3 t_color;

// コンストラクタ / 初期化
t_vec3 init_vec3(double x, double y, double z);
t_vec3 vec3_zero(void); // e{0,0,0} のためのコンストラクタ

// 基本的なベクトル演算
t_vec3 vec3_add(t_vec3 u, t_vec3 v);
t_vec3 vec3_add_triple(t_vec3 a, t_vec3 b, t_vec3 c);
t_vec3 vec3_sub(t_vec3 u, t_vec3 v);
t_vec3 vec3_mult(t_vec3 u, t_vec3 v); // 要素ごとの積
t_vec3 vec3_mult_scalar(t_vec3 v, double t);
t_vec3 vec3_div_scalar(t_vec3 v, double t);
t_vec3 vec3_neg(t_vec3 v); // 単項マイナス (-)
bool vec3_near_zero(t_vec3 v);
t_vec3 get_random_vec3_in_unit_sphere(t_xorshift64_state *state);
t_vec3 get_random_unit_vec3(t_xorshift64_state *state);
t_vec3  random_in_hemisphere(const t_vec3 normal, t_xorshift64_state *state);
t_vec3 get_random_vec3_in_unit_circle(t_xorshift64_state *state);
t_vec3 reflect(t_vec3 incoming, t_vec3 normal); //反射
t_vec3 refract(t_vec3 incoming, t_vec3 normal, double etai_over_etat); //over 割るまたは~分の~ etat transmitted（透過側）

// 長さ・ノルムの計算
double vec3_length_squared(t_vec3 v);
double vec3_length(t_vec3 v);

// 応用演算
double vec3_dot(t_vec3 u, t_vec3 v);
t_vec3 vec3_cross(t_vec3 u, t_vec3 v);
t_vec3 vec3_unit_vector(t_vec3 v); // 正規化 (長さ1のベクトルを返す)
t_vec3 init_random_vec3(t_xorshift64_state *state);
t_vec3 init_random_vec3_range(t_xorshift64_state *state, double min, double max);

// 色
t_color init_color(double red, double green, double blue);
t_color add_color(t_color a, t_color b);
t_color scale_color(t_color color, double scalar);
t_color dot_color(t_color color1, t_color color2);
void write_color(t_color pixel_color, const int num_samples_per_pixel);


#endif
