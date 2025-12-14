#include "ray.h"
#include "hittable_list.h"
#include "vec3.h"
#include "color.h"
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

    if (hit_hittable_list(ray, 0.001, INFINITY, &rec, world))
    {
        // t_vec3 normal_added = add_vec3(rec.normal_vector, init_vec3(1.0, 1.0, 1.0));
        // final_color_vec = mult_scalar_vec3(normal_added, 0.5);

        // t_vec3_color tmp_converter;
        // //散乱レイの目標点を決定
        // // t_point3 target = add_vec3(rec.intersection, rec.normal_vector);
        // // target = add_vec3(target ,get_random_unit_vec3(state));

        // t_point3 target = add_vec3(rec.intersection, random_in_hemisphere(rec.normal_vector, state));

        // //散乱方向の計算
        // t_vec3 scattered_direction = sub_vec3(target, rec.intersection);

        // //散乱レイを生成
        // t_ray scattered_ray = init_ray(rec.intersection, scattered_direction);

        // tmp_converter.color = ray_color(scattered_ray, world, state, num_recursions - 1);
        // t_vec3 incoming_color_vec = tmp_converter.vec;
        // final_color_vec = mult_scalar_vec3(incoming_color_vec, 0.5);

        t_ray scattered;
        t_color attenuation = rec.material.albedo;
        if (rec.material.scatters(ray, rec, &scattered, state))
        {
            return mult_vec3(ray_color(scattered, world, state, num_recursions - 1), attenuation);
        }
        return init_color(0, 0, 0);
    }
    else
    {
        //レイの方向ベクトルを単位ベクトルに正規化　背景の色にベクトルの長さは関係ない
        t_vec3 unit_direction = normalize_vec3(ray.direction);
        //垂直成分を[-1, 1]から[0, 1]の範囲にマップ (グラデーション係数t)
        double t = 0.5 * (unit_direction.y + 1.0);
        //線形補間(lerp):color = (1-t) * start_color + t * end_color
        t_vec3 white = init_vec3(1.0, 1.0, 1.0);
        t_vec3 sky_blue = init_vec3(0.5, 0.7, 1.0);
        //(1.0 - t) * color_a
        t_vec3 color_a = mult_scalar_vec3(white, 1.0 - t);
        t_vec3 color_b = mult_scalar_vec3(sky_blue, t);

        final_color_vec = add_vec3(color_a, color_b);
    }
    return final_color_vec;
}

size_t    init_world(t_hittable_list *world_list, t_sphere **sphere_ptrs, size_t num_obj, t_xorshift64_state *state)
{
    t_sphere    *current_sphere;
    // t_color     albedo;
    double      choose_mat;
    double      fuzz;
    double      refract_idx_glass = 1.5;
    size_t         ptr_index = 0; // sphere_ptrsへの格納インデックス

    // リストの初期化
    *world_list = init_hittable_list(num_obj);

    // ----------------------------------------------------
    // A. 大きな地面の球 (地面)
    // ----------------------------------------------------
    if (ptr_index < num_obj)
    {
        current_sphere = (t_sphere *)malloc(sizeof(t_sphere));
        if (!current_sphere) return 0;

        // C++: auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
        t_material ground_mat = init_lambertian_material(init_color(0.5, 0.5, 0.5), 0, 0);
        *current_sphere = init_sphere(init_vec3(0, -1000, 0), 1000.0, ground_mat);

        hittable_list_add(world_list, init_hittable(current_sphere, hit_object));
        sphere_ptrs[ptr_index++] = current_sphere;
    }


    // ----------------------------------------------------
    // B. ランダムな小さな球のグリッド (for ループ)
    // ----------------------------------------------------
    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            if (ptr_index >= num_obj - 3) // 後の3つの大きな球のためにスペースを確保
                goto ADD_LARGE_SPHERES;

            choose_mat = random_double(state);
            // C++: point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
            t_vec3 center = init_vec3(a + 0.9 * random_double(state),
                                      0.2,
                                      b + 0.9 * random_double(state));

            // C++: if ((center - vec3(4, 0.2, 0)).length() > 0.9)
            if (length_vec3(sub_vec3(center, init_vec3(4, 0.2, 0))) > 0.9)
            {
                current_sphere = (t_sphere *)malloc(sizeof(t_sphere));
                if (!current_sphere) goto ADD_LARGE_SPHERES; // メモリ不足で次のセクションへスキップ

                t_material sphere_material;

                if (choose_mat < 0.8) {
                    // 拡散 (Lambertian)
                    t_color albedo = mult_vec3(init_random_vec3(state), init_random_vec3(state));
                    // t_color albedo = init_color(0.8, 0.8, 0.8);
                    sphere_material = init_lambertian_material(albedo, 0, 0);
                } else if (choose_mat < 0.95) {
                    // 金属 (Metal)
                    t_color albedo = init_random_vec3_range(state, 0.5, 1);
                    fuzz = random_double_range(state, 0, 0.5);
                    sphere_material = init_metal_material(albedo, fuzz, 0);
                } else {
                    // 誘電体 (Glass)
                    sphere_material = init_dielectric_material(init_color(1.0, 1.0, 1.0), 0, refract_idx_glass);
                }

                *current_sphere = init_sphere(center, 0.2, sphere_material);
                hittable_list_add(world_list, init_hittable(current_sphere, hit_object));
                sphere_ptrs[ptr_index++] = current_sphere;
            }
        }
    }

    // ----------------------------------------------------
    // C. 大きな3つの球 (C++版の最後の3つの球)
    // ----------------------------------------------------
    ADD_LARGE_SPHERES:; // goto のターゲット

    // 1. (0, 1, 0) - ガラス
    if (ptr_index < num_obj) {
        current_sphere = (t_sphere *)malloc(sizeof(t_sphere));
        if (!current_sphere) return 0;
        t_material mat = init_dielectric_material(init_color(1.0, 1.0, 1.0), 0, refract_idx_glass);
        *current_sphere = init_sphere(init_vec3(0, 1, 0), 1.0, mat);
        hittable_list_add(world_list, init_hittable(current_sphere, hit_object));
        sphere_ptrs[ptr_index++] = current_sphere;
    }

    // 2. (-4, 1, 0) - 拡散
    if (ptr_index < num_obj) {
        current_sphere = (t_sphere *)malloc(sizeof(t_sphere));
        if (!current_sphere) return 0;
        t_material mat = init_lambertian_material(init_color(0.4, 0.2, 0.1), 0, 0);
        *current_sphere = init_sphere(init_vec3(-4, 1, 0), 1.0, mat);
        hittable_list_add(world_list, init_hittable(current_sphere, hit_object));
        sphere_ptrs[ptr_index++] = current_sphere;
    }

    // 3. (4, 1, 0) - 金属
    if (ptr_index < num_obj) {
        current_sphere = (t_sphere *)malloc(sizeof(t_sphere));
        if (!current_sphere) return 0;
        t_material mat = init_metal_material(init_color(0.7, 0.6, 0.5), 0.0, 0);
        *current_sphere = init_sphere(init_vec3(4, 1, 0), 1.0, mat);
        hittable_list_add(world_list, init_hittable(current_sphere, hit_object));
        sphere_ptrs[ptr_index++] = current_sphere;
    }
    // // 1. 中央の球
    // t_sphere *sphere1 = (t_sphere *)malloc(sizeof(t_sphere));
    // *sphere1 = init_sphere(init_vec3(0, 0, -1), 0.5, init_lambertian_material(init_color(0.1, 0.2, 0.5), fuzz, refract_idx_glass));
    // t_hittable hittable1 = init_hittable(sphere1, hit_object); //なぜ球とその関数を一緒にするんだっけ
    // hittable_list_add(world_list, hittable1);
    // sphere_ptrs[0] = sphere1; //開放用にポインタを保存

    return (ptr_index);
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
//         return (mult_scalar_vec3(normal_color, 0.5));
//     }

//     // 2.背景色の計算 (交差しなかった場合)

//     t_vec3 unit_direction;
//     double t;
//     t_color color_a;
//     t_color color_b;
//     t_color temp_color_a;
//     t_color temp_color_b;

//     //レイの方向ベクトルを単位ベクトルに正規化　背景の色にベクトルの長さは関係ない
//     unit_direction = normalize_vec3(ray.direction);
//     //垂直成分を[-1, 1]から[0, 1]の範囲にマップ (グラデーション係数t)
//     t = 0.5 * (unit_direction.y + 1.0);
//     //線形補間(lerp):color = (1-t) * start_color + t * end_color
//     color_a = vec3_new(1.0, 1.0, 1.0);
//     color_b = vec3_new(0.5, 0.7, 1.0);
//     //(1.0 - t) * color_a
//     temp_color_a = mult_scalar_vec3(color_a, 1.0 - t);
//     temp_color_b = mult_scalar_vec3(color_b, t);

//     return (add_vec3(temp_color_a, temp_color_b));
// }
