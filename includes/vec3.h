#ifndef VEC3_H
# define  VEC3_H

#include <math.h>

typedef struct s_vec3
{
    double x;
    double y;
    double z;
} t_vec3;

typedef t_vec3 t_point3;

// コンストラクタ / 初期化
t_vec3 init_vec3(double x, double y, double z);
t_vec3 vec3_zero(void); // e{0,0,0} のためのコンストラクタ

// 基本的なベクトル演算
t_vec3 vec3_add(t_vec3 u, t_vec3 v);
t_vec3 vec3_sub(t_vec3 u, t_vec3 v);
t_vec3 vec3_mult(t_vec3 u, t_vec3 v); // 要素ごとの積
t_vec3 vec3_mult_scalar(t_vec3 v, double t);
t_vec3 vec3_div_scalar(t_vec3 v, double t);
t_vec3 vec3_neg(t_vec3 v); // 単項マイナス (-)

// 長さ・ノルムの計算
double vec3_length_squared(t_vec3 v);
double vec3_length(t_vec3 v);

// 応用演算
double vec3_dot(t_vec3 u, t_vec3 v);
t_vec3 vec3_cross(t_vec3 u, t_vec3 v);
t_vec3 vec3_unit_vector(t_vec3 v); // 正規化 (長さ1のベクトルを返す)

#endif
