#include "../includes/ray.h"
#include "../includes/color.h"
#include "../includes/vec3.h"

//レイが何も物体に当たらなかった場合の背景色を計算する
t_color ray_color(t_ray r)
{
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
    temp_color_b = vec3_mult_scalar(color_a, t);

    return (vec3_add(temp_color_a, temp_color_b));
}