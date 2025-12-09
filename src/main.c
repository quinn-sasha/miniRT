#include <stdio.h>
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"

#define IMAGE_WIDTH 384
#define ASPECT_RATIO (16.0 / 9.0)
#define MAX_COLOR_VALUE 255
#define FOCAL_LENGTH 1.0 //カメラの焦点距離　視点からビューポートまでの距離

t_color ray_color(const t_ray ray, const t_hittable_list *world);
void    init_world(t_hittable_list *world, t_sphere **sphere_ptrs, size_t num_obj);
void    cleanup_world(t_hittable_list *world, t_sphere **sphere_ptrs, size_t num_obj);

int main(void)
{
    int row, col;
    int image_height;
    t_color pixel_color;
    t_ray ray;

    //画像設定
    image_height = (int)(IMAGE_WIDTH / ASPECT_RATIO);
    if (image_height < 1)
        image_height = 1;

    // PPM ヘッダの出力 (P3 フォーマット)
    // "P3"
    // [幅] [高さ]
    // [最大色値]
    printf("P3\n%d %d\n%d\n", IMAGE_WIDTH, image_height, MAX_COLOR_VALUE);

    //カメラパラメータの計算
    double viewport_height = 2.0;
    double viewport_width = ASPECT_RATIO * viewport_height;

    //視点(origin)は(0.0.0)
    t_point3 origin = vec3_new(0, 0, 0);
    //ビューポートの幅全体を表すベクトル
    t_vec3 horizontal = vec3_new(viewport_width, 0, 0);
    //ビューポートの高さ方向を表すベクトル
    t_vec3 vertical = vec3_new(0, viewport_height, 0);
    //ビューポートの左下隅(lower_left_corner)の座標計算
    // LLC = origin - horizontal / 2 - vertical / 2 - (0, 0, focal_length)
    t_vec3 h_half = vec3_mult_scalar(horizontal, 0.5);
    t_vec3 v_half = vec3_mult_scalar(vertical, 0.5);
    t_vec3 focus_vec = vec3_new(0, 0, FOCAL_LENGTH);

    t_point3  lower_left_corner = vec3_sub(origin, h_half);
              lower_left_corner = vec3_sub(lower_left_corner, v_half);
              lower_left_corner = vec3_sub(lower_left_corner, focus_vec);

    // 物体リストと個々の物体（球）をヒープに確保
    //TODO: 今はマクロで物体の数を定義しているが渡された数だけ確保するようにする
    const size_t num_objects = NUM_SCENE_OBJECTS;
    t_hittable_list world_list;
    t_sphere    *sphere_ptrs[num_objects];

    //物体リストと個々の物体をヒープに確保
    init_world(&world_list, sphere_ptrs, num_objects);

    for (row = image_height - 1; row >= 0; --row){
        fprintf(stderr, "\rScanlines remaining: %d ", row);
        fflush(stderr); //バッファを強制的にフラッシュしすぐに表示させる
        for (col = 0; col < IMAGE_WIDTH; ++col){
          //現在のピクセル位置(col, row)をビューポート上の0.0から1.0の間の座標(u, v)に変換　正規化座標
            double u = (double)col / (IMAGE_WIDTH - 1);
            double v = (double)row / (image_height - 1);
            //レイの方向ベクトルを計算
            //direction = lower_left_corner + u*horizontal + v*vertical - origin
            t_vec3 scaled_h = vec3_mult_scalar(horizontal, u);
            t_vec3 scaled_v = vec3_mult_scalar(vertical, v);

            t_vec3 direction = vec3_add(lower_left_corner, scaled_h);
                   direction = vec3_add(direction, scaled_v);
            //originは(0,0,0)なので省略

            //レイを初期化
            ray = ray_new(origin, direction);
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
