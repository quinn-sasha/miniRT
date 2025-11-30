#ifndef VECTOR3_H
#define VECTOR3_H

typedef struct s_vector3 {
  double x;
  double y;
  double z;
} t_vector3;

t_vector3 vec3_init(double x, double y, double z);
t_vector3 vec3_add(t_vector3 v1, t_vector3 v2);
t_vector3 vec3_sub(t_vector3 v1, t_vector3 v2);
double vec3_dot(t_vector3 v1, t_vector3 v2);
double vec3_length(t_vector3 v);
t_vector3 vec3_normalize(t_vector3 v);

#endif
