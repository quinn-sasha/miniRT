#ifndef COLOR_H
# define COLOR_H

typedef struct s_color {
  double red;
  double green;
  double blue;
} t_color;

// PPMフォーマットのピクセルデータを標準出力に出力する関数
t_color init_color(double red, double green, double blue);
t_color add_color(t_color a, t_color b);
t_color scale_color(t_color color, double scalar);
t_color dot_color(t_color color1, t_color color2);
void write_color(t_color pixel_color);

#endif
