#ifndef COLOR_H
#define COLOR_H

typedef struct s_color {
  double red;
  double green;
  double blue;
} t_color;

t_color init_color(double red, double green, double blue);
void write_color(int fd, t_color color);

#endif
