#include <stdio.h>
#include "../includes/color.h"
#include "../includes/vec3.h"
#include "../includes/ray.h"

#define IMAGE_WIDTH 384
#define ASPECT_RATIO (16.0 / 9.0)
#define MAX_COLOR_VALUE 255
#define FOCAL_LENGTH 1.0

t_color ray_color(t_ray r);

int main(void)
{
    int i, j;
    int image_height;
    t_color pixel_color;
    t_ray r;

    //画像設定
    image_height = (int)(IMAGE_WIDTH / ASPECT_RATIO);
    if (image_height < 1)
        image_height = 1; //最小高さは１

    // PPM ヘッダの出力 (P3 フォーマット)
    // "P3"
    // [幅] [高さ]
    // [最大色値]
    printf("P3\n%d %d\n%d\n", IMAGE_WIDTH, image_height, MAX_COLOR_VALUE);
    //カメラパラメータの計算
    double viewport_height = 2.0;
    double viewport_width = ASPECT_RATIO * viewport_height;

    t_point3 origin = vec3_new(viewport_width, 0, 0);
    t_vec3 vetrical;

    for (j = image_height - 1; j >= 0; --j){
        fprintf(stderr, "\rScanlines remaining: %d ", j);
        fflush(stderr); //バッファを強制的にフラッシュしすぐに表示させる
        for (i = 0; i < IMAGE_WIDTH; ++i){
            pixel_color = vec3_new(
                (double)i / (IMAGE_WIDTH - 1),
                (double)j / (IMAGE_HEIGHT - 1),
                0.25
            );
            write_color(pixel_color);
        }
    }
    fprintf(stderr, "\nDone.\n");
    return (0);
}
