#include <stdio.h>

#define IMAGE_WIDTH 256
#define IMAGE_HEIGHT 256
#define MAX_COLOR_VALUE 255

int main(void)
{
    int i, j;
    double r, g, b;
    int ir, ig, ib;

    // PPM ヘッダの出力 (P3 フォーマット)
    // "P3"
    // [幅] [高さ]
    // [最大色値]
    printf("P3\n%d %d\n%d\n", IMAGE_WIDTH, IMAGE_HEIGHT, MAX_COLOR_VALUE);
    for (j = IMAGE_HEIGHT - 1; j >= 0; --j){
        fprintf(stderr, "\rScanlines remaining: %d ", j);
        fflush(stderr); //バッファを強制的にフラッシュしすぐに表示させる
        for (i = 0; i < IMAGE_WIDTH; ++i){
            r = (double)i / (IMAGE_WIDTH - 1);
            g = (double)j / (IMAGE_HEIGHT - 1);
            b = 0.25;
            ir = (int)(255.999 * r);
            ig = (int)(255.999 * g);
            ib = (int)(255.999 * b);
            printf("%d %d %d\n", ir, ig, ib);   
        }
    }
    fprintf(stderr, "\nDone.\n");
    return (0);
}