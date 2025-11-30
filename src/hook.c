#include <minirt.h>
#include <stdlib.h>

int destroy_window(t_data *data) {
  mlx_destroy_window(data->mlx, data->window);
  data->window = NULL;
#ifdef __APPLE__
  exit(EXIT_SUCCESS);
#else
  return EXIT_SUCCESS;
#endif
  exit(EXIT_SUCCESS);
}

int handle_keypress(int keysym, t_data *data) {
  if (keysym == XK_Escape)
    return (destroy_window(data));
  return (0);
}
