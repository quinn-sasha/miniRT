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

// 基本的なベクトル演算
t_vec3 add_vec3(t_vec3 u, t_vec3 v);
t_vec3 add_triple_vec3(t_vec3 a, t_vec3 b, t_vec3 c);
t_vec3 sub_vec3(t_vec3 u, t_vec3 v);
t_vec3 mult_vec3(t_vec3 u, t_vec3 v); // 要素ごとの積
t_vec3 mult_scalar_vec3(t_vec3 v, double t);
t_vec3 div_scalar_vec3(t_vec3 v, double t);
t_vec3 negative_vec3(t_vec3 v); // 単項マイナス (-)
t_vec3 get_random_vec3_in_unit_sphere(t_xorshift64_state *state);
t_vec3 get_random_unit_vec3(t_xorshift64_state *state);
t_vec3  random_in_hemisphere(const t_vec3 normal, t_xorshift64_state *state);
t_vec3 get_random_vec3_in_unit_circle(t_xorshift64_state *state);
t_vec3 reflect(t_vec3 incoming, t_vec3 normal); //反射
t_vec3 refract(t_vec3 incoming, t_vec3 normal, double etai_over_etat); //over 割るまたは~分の~ etat transmitted（透過側）

// 長さ・ノルムの計算
double length_squared_vec3(t_vec3 v);
double length_vec3(t_vec3 v);

// 応用演算
double dot_vec3(t_vec3 u, t_vec3 v);
t_vec3 cross_vec3(t_vec3 u, t_vec3 v);
t_vec3 normalize_vec3(t_vec3 v); // 正規化 (長さ1のベクトルを返す)
t_vec3 init_random_vec3(t_xorshift64_state *state);
t_vec3 init_random_vec3_range(t_xorshift64_state *state, double min, double max);

// // 色
// t_color init_color(double red, double green, double blue);
// t_color add_color(t_color a, t_color b);
// t_color scale_color(t_color color, double scalar);
// t_color dot_color(t_color color1, t_color color2);
// void write_color(t_color pixel_color, const int num_samples_per_pixel);


#endif
