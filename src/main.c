#include <stdio.h>
#include "../includes/color.h"
#include "../includes/vec3.h"

#define IMAGE_WIDTH 256
#define IMAGE_HEIGHT 256
#define MAX_COLOR_VALUE 255

int main(void)
{
    int i, j;
    t_color pixel_color;

    // PPM ヘッダの出力 (P3 フォーマット)
    // "P3"
    // [幅] [高さ]
    // [最大色値]
    printf("P3\n%d %d\n%d\n", IMAGE_WIDTH, IMAGE_HEIGHT, MAX_COLOR_VALUE);
    for (j = IMAGE_HEIGHT - 1; j >= 0; --j){
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