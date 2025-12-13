#include "color.h"
#include "math.h"
#include "utilities.h"
#include <stdio.h>
#include <unistd.h>

t_color init_color(double red, double green, double blue) {
  t_color result;
  result.red = red;
  result.green = green;
  result.blue = blue;
  return result;
}

t_color add_color(t_color a, t_color b) {
  t_color new_color;
  new_color.red = a.red + b.red;
  new_color.green = a.green + b.green;
  new_color.blue = a.blue + b.blue;
  return new_color;
}

t_color scale_color(t_color color, double scalar) {
  t_color new_color;
  new_color.red = scalar * color.red;
  new_color.green = scalar * color.green;
  new_color.blue = scalar * color.blue;
  return new_color;
}

t_color dot_color(t_color color1, t_color color2) {
  t_color new_color;
  new_color.red = color1.red * color2.red;
  new_color.green = color1.green * color2.green;
  new_color.blue = color1.blue * color2.blue;
  return new_color;
}

// 各成分を[0, 255]に変換する
// 255.999 をかけることで、0.999...をかける場合でも白(255)になるようにする
void write_color(int fd, t_color color, int num_samples_per_pixel) {
  double red = color.red;
  double green = color.green;
  double blue = color.blue;

  double scalar = 1.0 / num_samples_per_pixel;
  red = sqrt(scalar * red);
  green = sqrt(scalar * green);
  blue = sqrt(scalar * blue);
  int r = 256 * clamp(red, 0.0, 0.999);
  int g = 256 * clamp(green, 0.0, 0.999);
  int b = 256 * clamp(blue, 0.0, 0.999);
  dprintf(fd, "%d %d %d\n", r, g, b);
}
