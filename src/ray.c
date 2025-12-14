#include "vec3.h"
#include "ray.h"

//初期化
t_ray init_ray(t_point3 origin, t_vec3 direction)
{
    t_ray r;
    r.origin = origin;
    r.direction = direction;
    return (r);
}

//レイ上の点P(t)の計算
t_point3 ray_at(t_ray r, double t)
{
    t_vec3 scaled_dir;

    //t * dir
    scaled_dir = mult_scalar_vec3(r.direction, t);
    //origin + (t * dir)
    return (add_vec3(r.origin, scaled_dir));
}
