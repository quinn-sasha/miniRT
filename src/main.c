#include "calculate_color.h"
#include "camera.h"
#include "color.h"
#include "hit_record.h"
#include "light.h"
#include "material.h"
#include "minilibx_utils.h"
#include "minirt.h"
#include "mlx.h"
#include "object_list.h"
#include "parse.h"
#include "random_number_generator.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ccalulate runtime
#include <time.h>

t_color calculate_color(t_ray ray, t_program *data, t_xorshift64_state *state,
                        int num_recursions) {
  t_hit_record record;
  t_color direct_light;
  t_color indirect_light;
  t_color ambient_effect;
  t_color final_ambient;
  t_range range;

  if (num_recursions <= 0)
    return (init_color(0, 0, 0));
  range.min_t = 0.001;
  range.max_t = INFINITY;
  if (hits_any_object(&data->head, ray, range, &record)) {
    direct_light = init_color(0, 0, 0);
    if (record.material.type == MAT_LAMBERTIAN ||
        record.material.type == MAT_METAL)
      direct_light = calculate_direct_lighting(&record, &data->head,
                                               &data->light, ray, range);
    indirect_light =
        calculate_indirect_lighting(record, state, ray, num_recursions, data);
    ambient_effect = scale_vec3(data->ambient.color, data->ambient.ratio);
    final_ambient = multiply_vec3(record.material.albedo, ambient_effect);
    return (clamp_color(
        add_triple_vec3(direct_light, indirect_light, final_ambient)));
  }
  return (calculate_background_color(ray));
}

t_color calculate_average_color(t_program *data, int x, int y) {
  t_color pixel_color = init_color(0, 0, 0);
  for (int sample = 0; sample < data->num_samples; sample++) {
    double x_offset = (x + random_double(&data->state)) / (WIDTH - 1);
    double y_offset = (y + random_double(&data->state)) / (HEIGHT - 1);
    t_ray ray = get_ray(data->camera, x_offset, y_offset);
    pixel_color = add_vec3(pixel_color, calculate_color(ray, data, &data->state,
                                                        data->max_recursions));
  }
  pixel_color = divide_vec3(pixel_color, data->num_samples);
  return pixel_color;
}

int render(t_program *data) {
  if (data->window == NULL)
    return (EXIT_SUCCESS);
  for (int y = 0; y < HEIGHT; y++) {
    printf("Scanlines remaining: %d\n", HEIGHT - y);
    for (int x = 0; x < WIDTH; x++) {
      t_color pixel_color = calculate_average_color(data, x, y);
      gamma_correction(&pixel_color);
      set_pixel_color(x, y, &data->img, rgb_to_integer(pixel_color));
    }
  }
  printf("Rendering done\n");
  mlx_put_image_to_window(data->mlx, data->window, data->img.mlx_img, 0, 0);
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  t_program data;
  parse(argc, argv, &data);
  init_mlx_resources(&data);
  set_mlx_hooks(&data);
  render(&data);
  mlx_loop(data.mlx);
  return EXIT_SUCCESS;
}
