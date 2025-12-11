#include "ray.h"
#include "hittable_list.h"
#include "vec3.h"
#include "sphere.h"
#include "random_number_generator.h"
#include <stdbool.h>
#include <math.h>

//拡散反射とレイの再帰を導入
//衝突点における法線ベクトルの先端が単位球の中心になる　単位球内のランダムなベクトルを加算
//散乱方向の決定 散乱レイの目標点target - 衝突点rec.p 　再帰　新しい散乱レイの色を計算するために関数が再帰的
//0.5 * ray_color()　拡散反射マテリアルにおける光の吸収（減衰）
//物体が見える色は(マテリアルの色)×（散乱レイから返ってきた光の色）
t_color ray_color(const t_ray ray, const t_hittable_list *world,
                  t_xorshift64_state *state, int num_recursions)
{
    if (num_recursions <= 0)
        return init_color(0, 0, 0);

    t_hit_record rec;
    t_vec3 final_color_vec;
    t_vec3_color converter;

    if (hit_hittable_list(ray, 0.001, INFINITY, &rec, world))
    {
        // t_vec3 normal_added = vec3_add(rec.normal_vector, init_vec3(1.0, 1.0, 1.0));
        // final_color_vec = vec3_mult_scalar(normal_added, 0.5);

        t_vec3_color tmp_converter;
        //散乱レイの目標点を決定
        // t_point3 target = vec3_add(rec.intersection, rec.normal_vector);
        // target = vec3_add(target ,get_random_unit_vec3(state));

        t_point3 target = vec3_add(rec.intersection, random_in_hemisphere(rec.normal_vector, state));

        //散乱方向の計算
        t_vec3 scattered_direction = vec3_sub(target, rec.intersection);

        //散乱レイを生成
        t_ray scattered_ray = init_ray(rec.intersection, scattered_direction);

        tmp_converter.color = ray_color(scattered_ray, world, state, num_recursions - 1);
        t_vec3 incoming_color_vec = tmp_converter.vec;
        final_color_vec = vec3_mult_scalar(incoming_color_vec, 0.5);
    }
    else
    {
        //レイの方向ベクトルを単位ベクトルに正規化　背景の色にベクトルの長さは関係ない
        t_vec3 unit_direction = vec3_unit_vector(ray.direction);
        //垂直成分を[-1, 1]から[0, 1]の範囲にマップ (グラデーション係数t)
        double t = 0.5 * (unit_direction.y + 1.0);
        //線形補間(lerp):color = (1-t) * start_color + t * end_color
        t_vec3 white = init_vec3(1.0, 1.0, 1.0);
        t_vec3 sky_blue = init_vec3(0.5, 0.7, 1.0);
        //(1.0 - t) * color_a
        t_vec3 color_a = vec3_mult_scalar(white, 1.0 - t);
        t_vec3 color_b = vec3_mult_scalar(sky_blue, t);

        final_color_vec = vec3_add(color_a, color_b);
    }
    converter.vec = final_color_vec;

    return converter.color;
}

void    init_world(t_hittable_list *world_list, t_sphere **sphere_ptrs, size_t num_obj)
{
    // リストの初期化 (NUM_SCENE_OBJECTS の数だけメモリを確保)
    *world_list = init_hittable_list(num_obj);
    // 1. 中央の球
    t_sphere *sphere1 = (t_sphere *)malloc(sizeof(t_sphere));
    *sphere1 = init_sphere(init_vec3(0, 0, -1), 0.5);
    t_hittable hittable1 = init_hittable(sphere1, hit_object); //なぜ球とその関数を一緒にするんだっけ
    hittable_list_add(world_list, hittable1);
    sphere_ptrs[0] = sphere1; //開放用にポインタを保存

    // 2. 地面の球
    t_sphere *sphere2 = (t_sphere *)malloc(sizeof(t_sphere));
    *sphere2 = init_sphere(init_vec3(0, -100.5, -1), 100.0);
    t_hittable hittable2 = init_hittable(sphere2, hit_sphere); //なぜ球とその関数を一緒にするんだっけ
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
