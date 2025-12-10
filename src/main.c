#include <stdio.h>
#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "math_utils.h"

#define MAX_COLOR_VALUE 255

t_color ray_color(const t_ray ray, const t_hittable_list *world, t_xorshift64_state *state, int num_recursions);
void    init_world(t_hittable_list *world, t_sphere **sphere_ptrs, size_t num_obj);
void    cleanup_world(t_hittable_list *world, t_sphere **sphere_ptrs, size_t num_obj);

int main(void)
{
    const double aspect_ratio  = (double)16 / 9; //width / height
    const int   image_width = 384;
    const int   image_height = image_width / aspect_ratio;
    const int   num_recursions = 50;

    // PPM ヘッダの出力 (P3 フォーマット)
    // "P3" [幅] [高さ] [最大色値]
    printf("P3\n%d %d\n%d\n", image_width, image_height, MAX_COLOR_VALUE);

    t_viewport viewport = init_viewport(aspect_ratio, 2.0 * aspect_ratio, 2.0);
    t_camera camera = init_camera(viewport, init_vec3(0, 0, 0), 1.0);

    // 物体リストと個々の物体（球）をヒープに確保
    //TODO: 今はマクロで物体の数を定義しているが渡された数だけ確保するようにする
    const size_t num_objects = NUM_SCENE_OBJECTS;
    t_hittable_list world_list;
    t_sphere    *sphere_ptrs[num_objects];

    //物体リストと個々の物体をヒープに確保
    init_world(&world_list, sphere_ptrs, num_objects);

    const  int num_samples_per_pixel = 100;
    t_xorshift64_state state;
    init_xorshift64_state(&state);
    for (int col = image_height - 1; col >= 0; --col){
        for (int row = 0; row < image_width; ++row){
            fprintf(stderr, "\rScanlines remaining: %d ", col);
            fflush(stderr); //バッファを強制的にフラッシュしすぐに表示させる

            t_color pixel_color = init_color(0, 0, 0);
            for (int sample = 0; sample < num_samples_per_pixel; sample++)
            {
                //現在のピクセル位置(col, row)をビューポート上の0.0から1.0の間の座標(u, v)に変換　正規化座標
                double x_offset = (row + random_double(&state)) / (image_width - 1);
                double y_offset = (col + random_double(&state)) / (image_height - 1);
                //レイの方向ベクトルを計算
                t_ray  ray = get_ray(camera, x_offset, y_offset);
                //レイの色を計算
                pixel_color = add_color(pixel_color, ray_color(ray, &world_list, &state, num_recursions));
            }
            //色を出力
            write_color(pixel_color, num_samples_per_pixel);
            // write_color(pixel_color);
        }
    }
    cleanup_world(&world_list, sphere_ptrs, num_objects);
    fprintf(stderr, "\nDone.\n");
    return (0);
}

//なぜ焦点距離だけ下がるのか
//レイの方向ベクトルの計算
