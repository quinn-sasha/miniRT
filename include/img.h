#ifndef IMG_H
#define IMG_H

typedef struct s_img {
  void *mlx_img;
  char *address;
  int bits_per_pixel;
  int row_size;
  int endian;
} t_img;

#endif // !IMG_H
