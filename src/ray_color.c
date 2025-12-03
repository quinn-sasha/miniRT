#include "ray.h"
#include "color.h"
#include "vec3.h"
#include <stdbool.h>
#include <math.h>

double hit_sphere(t_point3 center, double radius, t_ray r)
{
    // vec3 oc = r.origin() - center;
    t_vec3 oc = vec3_sub(r.origin, center);

    // a = D・D (方向ベクトルの長さの二乗)
    double a = vec3_length_squared(r.direction);

    // b = 2 * (D・OC)
    double half_b = vec3_dot(oc, r.direction);

    // c = OC・OC - r^2
    double c = vec3_length_squared(oc) - radius * radius;

    // 判別式: discriminant = b^2 - 4ac
    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0.0)
        return (-1.0);
    //近い交点の方だけ扱う
    double t_hit = (-half_b - sqrt(discriminant)) / a;
    //t < 0の交点があっても無視する判定はray_colorに任せる
    return (t_hit);
}

//   (P(t) - C)⋅(P(t) - C) = r^2 レイが球と交わるならあるｔでP(t)が球の方程式を満たす。
//   t^2b⋅b+2tb⋅(A−C)+(A−C)⋅(A−C)−r^2=0
//　　今のままだとt < 0で交わる場合にもピクセルが赤くなる。

t_color ray_color(t_ray r)
{
    //仮の球体　中心(0, 0, -1), 半径0.5
    t_point3 sphere_center = vec3_new(0, 0, -1);
    double sphere_radius = 0.5;

    // 1.球との交差判定
    double t_hit = hit_sphere(sphere_center, sphere_radius, r);

    if (t_hit > 0.0)
    {
        //法線の計算と可視化

        //a.交点P(t)を計算
        t_point3 p = ray_at(r, t_hit);

        //b.外向きの法線ベクトル N を計算
        //球だと交点から中心を引いたベクトルが法線と同じ向き
        t_vec3 outward_normal = vec3_sub(p, sphere_center);

        //c.法線を単位ベクトルに正規化
        t_vec3 N = vec3_unit_vector(outward_normal);

        //d.法線ベクトルNの成分 [-1, 1] を色 [0, 1]にマッピングし可視化
        t_color normal_color = vec3_new(N.x + 1.0, N.y + 1.0, N.z + 1.0);
        return (vec3_mult_scalar(normal_color, 0.5));
    }

    // 2.背景色の計算 (交差しなかった場合)

    t_vec3 unit_direction;
    double t;
    t_color color_a;
    t_color color_b;
    t_color temp_color_a;
    t_color temp_color_b;

    //レイの方向ベクトルを単位ベクトルに正規化　背景の色にベクトルの長さは関係ない
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
