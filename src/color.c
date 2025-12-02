#include "color.h"

void write_color(t_color pixel_color)
{
    int ir, ig, ib;

    ir = (int)(255.999 * pixel_color.x);
    ig = (int)(255.999 * pixel_color.y);
    ib = (int)(255.999 * pixel_color.z);
    printf("%d %d %d\n", ir, ig, ib);
}
