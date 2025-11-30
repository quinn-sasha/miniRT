#include "minirt.h"

// Ignore error handling
void init_mlx_resources(t_data *data) {
  data->mlx = NULL;
  data->window = NULL;
  data->mlx = mlx_init();
  data->window = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "root");
}

void init_mlx(t_data *data) {
  init_mlx_resources(data);
  mlx_hook(data->window, KeyPress, KeyPressMask, &handle_keypress, &data);
  mlx_hook(data->window, DestroyNotify, 0, &destroy_window, &data);
}

void free_mlx_resources_if_allocated(t_data *data) {
  if (data->window)
    mlx_destroy_window(data->mlx, data->window);
#ifdef __linux__
  mlx_destroy_display(data->mlx);
#endif
  free(data->mlx);
}
