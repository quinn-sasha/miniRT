#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

t_color init_color(double red, double green, double blue);
void write_color(int fd, t_color color, int num_samples_per_pixel);

#endif
