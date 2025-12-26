#include "calculate_color.h"
#include "camera.h"
#include "color.h"
#include "hit_record.h"
#include "light.h"
#include "material.h"
#include "minilibx_utils.h"
#include "mlx.h"
#include "object_list.h"
#include "parse.h"
#include "random_number_generator.h"
#include "ray.h"
#include "vec3.h"
#include "minirt.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ccalulate runtime
#include <time.h>

int render(t_program *data) {
  if (data->window == NULL)
    return (EXIT_SUCCESS);

  t_xorshift64_state state;
  init_xorshift64_state(&state);

  printf("Rendering started\n");
  clock_t begin = clock();
  for (int y = 0; y < HEIGHT; y++) {
    printf("Scanlines reamaining: %d\n", HEIGHT - y);
    for (int x = 0; x < WIDTH; x++) {

      t_color pixel_color = init_color(0, 0, 0);
      for (int sample = 0; sample < data->num_samples_per_pixel; sample++) {
        double x_offset = (x + random_double(&state)) / (WIDTH - 1);
        double y_offset = (y + random_double(&state)) / (HEIGHT - 1);
        t_ray ray = get_ray(data->camera, x_offset, y_offset);
        pixel_color = add_vec3(
            pixel_color, calculate_color(ray, data, &state, data->max_recursions));
      }
      pixel_color = divide_vec3(pixel_color, data->num_samples_per_pixel);
      gamma_correction(&pixel_color);
      set_pixel_color(x, y, &data->img, rgb_to_integer(pixel_color));
    }
  }
  mlx_put_image_to_window(data->mlx, data->window, data->img.mlx_img, 0, 0);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time spent: %lf seconds\n", time_spent);
  printf("Rendering done\n");
  return EXIT_SUCCESS;
}

static void set_render_config(t_program *data, int max_recursions,
                                    int num_samples_per_pixel)
{
  data->max_recursions = max_recursions;
  data->num_samples_per_pixel = num_samples_per_pixel;
}

int main(int argc, char *argv[])
{
  t_program data;

  parse(argc, argv, &data);
  set_render_config(&data, 50, 100);
  init_mlx_resources(&data);
  set_mlx_hooks(&data);
  render(&data);
  mlx_loop(data.mlx);
  return EXIT_SUCCESS;
}
