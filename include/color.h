#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

t_color init_color(double red, double green, double blue);
void 		gamma_correction(t_color *color);
uint32_t rgb_to_integer(t_color color);
t_color clamp_color(t_color color);

#endif
