#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"

typedef struct s_light {
  t_vec3 pos;
  double brightness_ratio;
  t_color color;
} t_light;

typedef struct s_ambient {
  double ratio;
  t_color color;
} t_ambient;

t_light init_light(t_vec3 pos, double brightness_ratio, t_color color);
t_ambient init_ambient(double brightness_ratio, t_color color);

#endif
