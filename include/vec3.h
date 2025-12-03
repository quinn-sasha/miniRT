#ifndef VEC3_H
#define VEC3_H

typedef struct s_vec3 {
  double x;
  double y;
  double z;
} t_vec3;

t_vec3 vec3_init(double x, double y, double z);
t_vec3 vec3_scale(t_vec3 v, double scalar);
t_vec3 vec3_inverse(t_vec3 v);
t_vec3 vec3_divide(t_vec3 v, double scalar);
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_add_triple(t_vec3 a, t_vec3 b, t_vec3 c);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
double vec3_length(t_vec3 v);
double vec3_dot(t_vec3 a, t_vec3 b);
t_vec3 vec3_normalize(t_vec3 v);
void vec3_print(t_vec3 v);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);

#endif
