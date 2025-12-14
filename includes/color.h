#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

t_color init_color(double red, double green, double blue);
t_color add_color(t_color a, t_color b);
t_color scale_color(t_color color, double scalar);
t_color dot_color(t_color color1, t_color color2);
t_color  average_samples(t_color pixel_color, const int num_samples_per_pixel);
t_color gamma_correct(t_color pixel_color);
void		write_color(t_color pixel_color);

#endif
