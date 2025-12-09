#include <stdio.h>
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "math_utils.h"

#define MAX_COLOR_VALUE 255

t_color ray_color(const t_ray ray, const t_hittable_list *world);
void    init_world(t_hittable_list *world, t_sphere **sphere_ptrs, size_t num_obj);
void    cleanup_world(t_hittable_list *world, t_sphere **sphere_ptrs, size_t num_obj);

int main(void)
{
    const double aspect_ratio  = (double)16 / 9; //width / height
    const int   image_width = 384;
    const int   image_height = image_width / aspect_ratio;
    t_ray ray;

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

    t_xorshift64_state state;
    init_xorshift64_state(&state);
    for (int col = image_height - 1; col >= 0; --col){
        for (int row = 0; row < image_width; ++row){
            fprintf(stderr, "\rScanlines remaining: %d ", col);
            fflush(stderr); //バッファを強制的にフラッシュしすぐに表示させる

            t_color pixel_color = init_color(0, 0, 0);
          //現在のピクセル位置(col, row)をビューポート上の0.0から1.0の間の座標(u, v)に変換　正規化座標
            double u = (double)col / (image_width - 1);
            double v = (double)row / (image_height - 1);
            //レイの方向ベクトルを計算
            //direction = lower_left_corner + u*horizontal + v*vertical - origin
            t_vec3 scaled_h = vec3_mult_scalar(horizontal, u);
            t_vec3 scaled_v = vec3_mult_scalar(vertical, v);

            t_vec3 direction = vec3_add(camera.lower_left_corner, scaled_h);
                   direction = vec3_add(direction, scaled_v);
            //originは(0,0,0)なので省略

            //レイを初期化
            ray = init_ray(origin, direction);
            //レイの色を計算
            pixel_color = ray_color(ray, &world_list);
            //色を出力
            write_color(pixel_color);
        }
    }
    cleanup_world(&world_list, sphere_ptrs, num_objects);
    fprintf(stderr, "\nDone.\n");
    return (0);
}

//なぜ焦点距離だけ下がるのか
//レイの方向ベクトルの計算
