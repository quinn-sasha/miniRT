#include "color.h"

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

// void write_color(t_color pixel_color)
// {
//     int ir, ig, ib;

//     ir = (int)(255.999 * pixel_color.x);
//     ig = (int)(255.999 * pixel_color.y);
//     ib = (int)(255.999 * pixel_color.z);
//     printf("%d %d %d\n", ir, ig, ib);
// }
