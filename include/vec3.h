#ifndef VEC3_H
#define VEC3_H

#include "random_number_generator.h"

typedef struct s_vec3 {
  double x;
  double y;
  double z;
} t_vec3;

typedef t_vec3 t_color;

t_vec3 init_vec3(double x, double y, double z);
t_vec3 scale_vec3(t_vec3 v, double scalar);
t_vec3 inverse_vec3(t_vec3 v);
t_vec3 divide_vec3(t_vec3 v, double scalar);
t_vec3 add_vec3(t_vec3 a, t_vec3 b);
t_vec3 add_triple_vec3(t_vec3 a, t_vec3 b, t_vec3 c);
t_vec3 sub_vec3(t_vec3 a, t_vec3 b);
double length_squared_vec3(t_vec3 v);
double length_vec3(t_vec3 v);
double dot_vec3(t_vec3 a, t_vec3 b);
t_vec3 multiply_vec3(t_vec3 a, t_vec3 b);
t_vec3 normalize_vec3(t_vec3 v);
t_vec3 negative_vec3(t_vec3 v);
t_vec3 cross_vec3(t_vec3 a, t_vec3 b);
t_vec3 init_random_vec3(t_xorshift64_state *state);
t_vec3 init_random_vec3_range(t_xorshift64_state *state, double min,
                              double max);
t_vec3 init_random_vec3_in_unit_sphere(t_xorshift64_state *state);
t_vec3 random_in_hemisphere(const t_vec3 normal, t_xorshift64_state *state);
t_vec3 init_random_vec3_in_unit_circle(t_xorshift64_state *state);
t_vec3 init_random_unit_vec3(t_xorshift64_state *state);
t_vec3 reflect(t_vec3 incoming, t_vec3 normal);
t_vec3 refract(t_vec3 incoming, t_vec3 n, double eta_in_over_etat);

#endif
