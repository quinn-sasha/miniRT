#include "color.h"
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

// 各成分を[0, 255]に変換する
// 255.999 をかけることで、0.999...をかける場合でも白(255)になるようにする
void write_color(int fd, t_color color) {
  int red = 255.999 * color.red;
  int green = 255.999 * color.green;
  int blue = 255.999 * color.blue;
  dprintf(fd, "%d %d %d\n", red, green, blue);
}
