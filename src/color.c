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

// 各成分を[0, 255]に変換する
// 255.999 をかけることで、0.999...をかける場合でも白(255)になるようにする
void write_color(int fd, t_color color, int num_samples_per_pixel) {
  double red = color.x;
  double green = color.y;
  double blue = color.z;

  double scalar = 1.0 / num_samples_per_pixel;
  red = sqrt(scalar * red);
  green = sqrt(scalar * green);
  blue = sqrt(scalar * blue);
  int r = 256 * clamp(red, 0.0, 0.999);
  int g = 256 * clamp(green, 0.0, 0.999);
  int b = 256 * clamp(blue, 0.0, 0.999);
  dprintf(fd, "%d %d %d\n", r, g, b);
}
