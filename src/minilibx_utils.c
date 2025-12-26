#include "minilibx_utils.h"
#include "error_utils.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

// parse で動的に確保したものはfree()を呼び出さずに終了する
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
    handle_mlx_error(data);
  data->img.mlx_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
  if (!data->img.mlx_img)
    handle_mlx_error(data);
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

int destroy_window(t_program *data) {
  mlx_destroy_window(data->mlx, data->window);
  data->window = NULL;
  destroy_mlx_resources_if_allocated(data);
  destroy_object_list(&data->head);
  exit(EXIT_SUCCESS);
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
