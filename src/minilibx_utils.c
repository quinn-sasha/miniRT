#include "minilibx_utils.h"
#include "error.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

void set_pixel_color(int x, int y, t_img *img, uint32_t color) {
  int bytes_per_pixel;
  int offset;
  char *pixel_addr;

  bytes_per_pixel = img->bits_per_pixel / 8;
  offset = img->row_size * y + x * bytes_per_pixel;
  pixel_addr = img->address + offset;
  *(uint32_t *)pixel_addr = color;
}

void init_mlx_resources(t_program *data) {
  t_img *image;

  data->mlx = NULL;
  data->window = NULL;
  data->img.mlx_img = NULL;
  data->mlx = mlx_init();
  if (!data->mlx)
    error_exit(MLX_ERROR);
  data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
  if (!data->window)
    error_exit(MLX_ERROR);
  data->img.mlx_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
  if (!data->img.mlx_img)
    error_exit(MLX_ERROR);
  image = &data->img;
  image->address = mlx_get_data_addr(image->mlx_img, &image->bits_per_pixel,
                                     &image->row_size, &image->endian);
  (void)image->endian;
}

void destroy_mlx_resources_if_allocated(t_program *data) {
  if (data->img.mlx_img) {
    mlx_destroy_image(data->mlx, data->img.mlx_img);
  }
  if (data->window) {
    mlx_destroy_window(data->mlx, data->window);
  }
#ifdef __linux__
  mlx_destroy_display(data->mlx);
#endif
  free(data->mlx);
}

static int destroy_window(t_program *data) {
  mlx_destroy_window(data->mlx, data->window);
  data->window = NULL;
  return (0);
}

static int handle_keypress(int keysymbol, t_program *data) {
  if (keysymbol == XK_ESCAPE)
    return (destroy_window(data));
  return (0);
}

void set_mlx_hooks(t_program *data) {
  mlx_hook(data->window, KEYPRESS, KEYPRESSMASK, handle_keypress, data);
  mlx_hook(data->window, DESTROYNOTIFY, 0, destroy_window, data);
}
