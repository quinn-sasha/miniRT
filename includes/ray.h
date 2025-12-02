#ifndef RAY_H
# define RAY_H

#include "vec3.h"

typedef struct s_ray
{
    t_point3 origin;
    t_vec3 direction;
} t_ray;

t_ray ray_new(t_point3 origin, t_vec3 direction);
//レイ上の点P(t) = O + tDを計算
t_point3 ray_at(t_ray r, double t);

#endif
