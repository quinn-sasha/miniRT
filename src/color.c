#include "color.h"
#include "math.h"
#include "utilities.h"
#include "vec3.h"
#include <stdio.h>

t_color init_color(double red, double green, double blue) {
  t_color color;
  color.x = clamp(red, 0.0, 1.0);
  color.y = clamp(green, 0.0, 1.0);
  color.z = clamp(blue, 0.0, 1.0);
  return color;
}

void gamma_correction(t_color *color) {
  color->x = sqrt(color->x);
  color->y = sqrt(color->y);
  color->z = sqrt(color->z);
}

uint32_t rgb_to_integer(t_color color) {
  double red = color.x;
  double green = color.y;
  double blue = color.z;

  int r = 256 * clamp(red, 0.0, 0.999);
  int g = 256 * clamp(green, 0.0, 0.999);
  int b = 256 * clamp(blue, 0.0, 0.999);
  return (r << 16 | g << 8 | b);
}
