#include "vec3.h"
#include "math.h"
#include "utils.h"
#include <stdio.h>

t_color init_color(double red, double green, double blue) {
  t_color color;
  color.x = red;
  color.y = green;
  color.z = blue;
  return color;
}

// t_color add_color(t_color a, t_color b) {
//   t_color new_color;
//   new_color.red = a.red + b.red;
//   new_color.green = a.green + b.green;
//   new_color.blue = a.blue + b.blue;
//   return new_color;
// }

// t_color scale_color(t_color color, double scalar) {
//   t_color new_color;
//   new_color.red = scalar * color.red;
//   new_color.green = scalar * color.green;
//   new_color.blue = scalar * color.blue;
//   return new_color;
// }

// t_color dot_color(t_color color1, t_color color2) {
//   t_color new_color;
//   new_color.red = color1.red * color2.red;
//   new_color.green = color1.green * color2.green;
//   new_color.blue = color1.blue * color2.blue;
//   return new_color;
// }

void  write_color(t_color color, const int num_samples_per_pixel)
{
  double red = color.x;
  double green = color.y;
  double blue = color.z;

  double scale = 1.0 / num_samples_per_pixel;
  red = sqrt(red * scale);
  green = sqrt(green * scale);
  blue = sqrt(blue * scale);

  int r = 256 * clamp(red, 0.0, 0.999);
  int g = 256 * clamp(green, 0.0, 0.999);
  int b = 256 * clamp(blue, 0.0, 0.999);

  printf("%d %d %d\n", r, g, b);
}
