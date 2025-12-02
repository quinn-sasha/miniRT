#include "ray.h"
#include "color.h"
#include "vec3.h"
#include <stdbool.h>

bool hit_sphere(t_point3 center, double radius, t_ray r)
{
    // vec3 oc = r.origin() - center;
    t_vec3 oc = vec3_sub(r.origin, center);

    // a = D・D (方向ベクトルの長さの二乗)
    double a = vec3_length_squared(r.direction);

    // b = 2 * (D・OC)
    double b = 2.0 * vec3_dot(oc, r.direction);

    // c = OC・OC - r^2
    double c = vec3_length_squared(oc) - radius * radius;

    // 判別式: discriminant = b^2 - 4ac
    double discriminant = b * b - 4 * a * c;

    // return (discriminant > 0);
    // 判別式が正であれば、実数解（交点）が存在する
    return (discriminant > 0.0);
}


//レイが何も物体に当たらなかった場合の背景色を計算する
t_color ray_color(t_ray r)
{
    //仮の球体　中心(0, 0, -1), 半径0.5
    t_point3 sphere_center = vec3_new(0, 0, -1);
    double sphere_radius = 0.5;

    // 1.球との交差判定
    double t_hit = hit_sphere(sphere_center, sphere_radius, r);

    if (t_hit > 0.0)
    {
        return (vec3_new(1.0, 0.0, 0.0));
    }
    // 2.背景色の計算 (交差しなかった場合)

    t_vec3 unit_direction;
    double t;
    t_color color_a;
    t_color color_b;
    t_color temp_color_a;
    t_color temp_color_b;

    //レイの方向ベクトルを単位ベクトルに正規化
    unit_direction = vec3_unit_vector(r.direction);
    //垂直成分を[-1, 1]から[0, 1]の範囲にマップ (グラデーション係数t)
    t = 0.5 * (unit_direction.y + 1.0);
    //線形補間(lerp):color = (1-t) * start_color + t * end_color
    color_a = vec3_new(1.0, 1.0, 1.0);
    color_b = vec3_new(0.5, 0.7, 1.0);
    //(1.0 - t) * color_a
    temp_color_a = vec3_mult_scalar(color_a, 1.0 - t);
    temp_color_b = vec3_mult_scalar(color_b, t);

    return (vec3_add(temp_color_a, temp_color_b));
}
