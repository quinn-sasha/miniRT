#include "ray.h"
#include "hittable_list.h"
#include "color.h"
#include "vec3.h"
#include "sphere.h"
#include <stdbool.h>
#include <math.h>

t_color ray_color(const t_ray ray, const t_hittable_list *world)
{
    t_hit_record rec;

    if (hit_hittable_list(ray, 0.001, INFINITY, &rec, world))
    {
        t_color normal_added = vec3_add(rec.normal_vector, vec3_new(1.0, 1.0, 1.0));
        return (vec3_mult_scalar(normal_added, 0.5));
    }

    //レイの方向ベクトルを単位ベクトルに正規化　背景の色にベクトルの長さは関係ない
    t_vec3 unit_direction = vec3_unit_vector(ray.direction);
    //垂直成分を[-1, 1]から[0, 1]の範囲にマップ (グラデーション係数t)
    double t = 0.5 * (unit_direction.y + 1.0);
    //線形補間(lerp):color = (1-t) * start_color + t * end_color
    t_color white = vec3_new(1.0, 1.0, 1.0);
    t_color sky_blue = vec3_new(0.5, 0.7, 1.0);
    //(1.0 - t) * color_a
    t_color color_a = vec3_mult_scalar(white, 1.0 - t);
    t_color color_b = vec3_mult_scalar(sky_blue, t);

    return (vec3_add(color_a, color_b));
}

void    init_world(t_hittable_list *world_list, t_sphere **sphere_ptrs, size_t num_obj)
{
    // リストの初期化 (NUM_SCENE_OBJECTS の数だけメモリを確保)
    *world_list = hittable_list_new(num_obj);
    // 1. 中央の球
    t_sphere *sphere1 = (t_sphere *)malloc(sizeof(t_sphere));
    *sphere1 = sphere_new(vec3_new(0, 0, -1), 0.5);
    t_hittable hittable1 = hittable_new(sphere1, hit_sphere); //なぜ球とその関数を一緒にするんだっけ
    hittable_list_add(world_list, hittable1);
    sphere_ptrs[0] = sphere1; //開放用にポインタを保存

    // 2. 地面の球
    t_sphere *sphere2 = (t_sphere *)malloc(sizeof(t_sphere));
    *sphere2 = sphere_new(vec3_new(0, -100.5, -1), 100.0);
    t_hittable hittable2 = hittable_new(sphere2, hit_sphere); //なぜ球とその関数を一緒にするんだっけ
    hittable_list_add(world_list, hittable2);
    sphere_ptrs[1] = sphere2; //開放用にポインタを保存
}

void    cleanup_world(t_hittable_list *world, t_sphere **sphere_ptrs, size_t num_obj)
{
    for (size_t i = 0; i < num_obj; i++)
    {
        if (sphere_ptrs[i])
            free(sphere_ptrs[i]);
    }
    hittable_list_clear(world);
}


// t_color ray_color(t_ray ray, const t_hittable_list *world)
// {
//     //仮の球体　中心(0, 0, -1), 半径0.5
//     t_sphere sphere = sphere_new(vec3_new(0, 0, -1), 0.5);
//     t_hit_record hit_rec;

//     double min_t = 0.001;
//     double max_t = 1000.0;

//     if (hit_sphere(ray, min_t, max_t, &hit_rec, &sphere))
//     {
//         //法線ベクトルNの成分 [-1, 1] を色 [0, 1]にマッピングし可視化
//         t_vec3 N = hit_rec.normal_vector;

//         t_color normal_color = vec3_new(N.x + 1.0, N.y + 1.0, N.z + 1.0);
//         return (vec3_mult_scalar(normal_color, 0.5));
//     }

//     // 2.背景色の計算 (交差しなかった場合)

//     t_vec3 unit_direction;
//     double t;
//     t_color color_a;
//     t_color color_b;
//     t_color temp_color_a;
//     t_color temp_color_b;

//     //レイの方向ベクトルを単位ベクトルに正規化　背景の色にベクトルの長さは関係ない
//     unit_direction = vec3_unit_vector(ray.direction);
//     //垂直成分を[-1, 1]から[0, 1]の範囲にマップ (グラデーション係数t)
//     t = 0.5 * (unit_direction.y + 1.0);
//     //線形補間(lerp):color = (1-t) * start_color + t * end_color
//     color_a = vec3_new(1.0, 1.0, 1.0);
//     color_b = vec3_new(0.5, 0.7, 1.0);
//     //(1.0 - t) * color_a
//     temp_color_a = vec3_mult_scalar(color_a, 1.0 - t);
//     temp_color_b = vec3_mult_scalar(color_b, t);

//     return (vec3_add(temp_color_a, temp_color_b));
// }
