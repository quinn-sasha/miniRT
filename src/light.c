#include "light.h"

t_light init_light(t_vec3 pos, double brightness_ratio, t_color color) {
  t_light light;
  light.pos = pos;
  light.brightness_ratio = brightness_ratio;
  light.color = color;
  return light;
}

t_ambient init_ambient(double brightness_ratio, t_color color) {
  t_ambient ambient;
  ambient.ratio = brightness_ratio;
  ambient.color = color;
  return ambient;
}
