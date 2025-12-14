#include <stdio.h>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "math_utils.h"

#define MAX_COLOR_VALUE 255
#define MAX_SCENE_OBJECTS 10000

t_color ray_color(const t_ray ray, const t_hittable_list *world, t_xorshift64_state *state, int num_recursions);
size_t    init_world(t_hittable_list *world, t_sphere **sphere_ptrs, size_t num_obj, t_xorshift64_state *state);
void    cleanup_world(t_hittable_list *world, t_sphere **sphere_ptrs, size_t num_obj);

int main(void)
{
    t_screen screen = init_screen(384, 216);
    t_vec3 lookfrom = init_vec3(13, 2, 3);
    t_vec3 lookat = init_vec3(0, 0, 0);
    t_vec3 view_up = init_vec3(0, 1, 0);
    double vfov = 20.0;
    double aperture = 0.1;
    double focus_dist = length_vec3(sub_vec3(lookat, lookfrom));
    t_camera camera = init_camera(lookfrom, lookat, view_up, screen.aspect_ratio,
                                  vfov, aperture, focus_dist);

    // PPM ヘッダの出力 (P3 フォーマット)
    // "P3" [幅] [高さ] [最大色値]
    printf("P3\n%d %d\n%d\n", screen.width, screen.height, MAX_COLOR_VALUE);

    // 物体リストと個々の物体（球）をヒープに確保
    //TODO: 今はマクロで物体の数を定義しているが渡された数だけ確保するようにする
    const size_t max_objects = MAX_SCENE_OBJECTS;
    t_hittable_list world_list;
    t_sphere    *sphere_ptrs[max_objects];


    //物体リストと個々の物体をヒープに確保
    t_xorshift64_state state;
    init_xorshift64_state(&state);
    size_t count_objects = init_world(&world_list, sphere_ptrs, max_objects, &state);

    const   int max_recursions = 50;
    const  int num_samples_per_pixel = 100;
    for (int col = screen.height - 1; col >= 0; --col){
        for (int row = 0; row < screen.width; ++row){
            fprintf(stderr, "\rScanlines remaining: %d ", col);
            fflush(stderr); //バッファを強制的にフラッシュしすぐに表示させる

            t_color pixel_color = init_color(0, 0, 0);
            for (int sample = 0; sample < num_samples_per_pixel; sample++)
            {
                //現在のピクセル位置(col, row)をビューポート上の0.0から1.0の間の座標(u, v)に変換　正規化座標
                double x_offset = (row + random_double(&state)) / (screen.width - 1);
                double y_offset = (col + random_double(&state)) / (screen.height - 1);
                //レイの方向ベクトルを計算
                t_ray  ray = get_ray(camera, x_offset, y_offset, &state);
                //レイの色を計算
                pixel_color = add_vec3(pixel_color, ray_color(ray, &world_list, &state, max_recursions));
            }
            //色を出力
            t_color averaged_color = average_samples(pixel_color, num_samples_per_pixel);
            t_color gamma_corrected_color = gamma_correct(averaged_color);
            write_color(gamma_corrected_color);
        }
    }
    cleanup_world(&world_list, sphere_ptrs, count_objects);
    fprintf(stderr, "\nDone.\n");
    return (0);
}

//なぜ焦点距離だけ下がるのか
//レイの方向ベクトルの計算
