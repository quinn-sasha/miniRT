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
#include "sphere.h"
#include "vec3.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ccalulate runtime
#include <time.h>

static void generate_random_scene(t_scene_object *head,
                                  t_xorshift64_state *state) {
  t_material ground_material;
  t_material material1;
  t_material material2;
  t_material material3;

  ground_material = init_lambertian_material(init_color(0.5, 0.5, 0.5));
  add_sphere(head, new_sphere(init_vec3(0, -1000, 0), 1000, ground_material));
  // (void)state;
  for (int i = -11; i < 11; i++) {
    for (int j = -11; j < 11; j++) {
      t_vec3 center = init_vec3(i + 0.9 * random_double(state), 0.2,
                                j + 0.9 * random_double(state));
      if (length_vec3(sub_vec3(center, init_vec3(4, 0.2, 0))) <= 0.9)
        continue;
      double material_decision = random_double(state);
      t_material sphere_material;
      if (material_decision < 0.8) {
        t_color albedo =
            multiply_vec3(init_random_vec3(state), init_random_vec3(state));
        sphere_material = init_lambertian_material(albedo);
        add_sphere(head, new_sphere(center, 0.2, sphere_material));
        continue;
      }
      if (material_decision < 0.95) {
        t_color albedo = init_random_vec3_range(state, 0.5, 1);
        double fuzziness = random_double_range(state, 0, 0.5);
        sphere_material = init_metal_material(albedo, fuzziness);
        add_sphere(head, new_sphere(center, 0.2, sphere_material));
        continue;
      }
      sphere_material = init_dielectric_material(1.5); // glass: 1.5
      add_sphere(head, new_sphere(center, 0.2, sphere_material));
    }
  }
  material1 = init_dielectric_material(1.5);
  add_sphere(head, new_sphere(init_vec3(0, 1, 0), 1.0, material1));
  material2 = init_lambertian_material(init_color(0.4, 0.2, 0.1));
  add_sphere(head, new_sphere(init_vec3(-4, 1, 0), 1.0, material2));
  material3 = init_metal_material(init_color(0.7, 0.6, 0.5), 0.0);
  add_sphere(head, new_sphere(init_vec3(4, 1, 0), 1.0, material3));
}

t_color calculate_color(t_ray ray, t_program *data, t_xorshift64_state *state,
                        int num_recursions) {
  t_hit_record record;
  t_color direct_light;
  t_color indirect_light;
  t_color ambient_effect;
  t_color final_ambient;

  if (num_recursions <= 0)
    return (init_color(0, 0, 0));
  if (hits_any_object(&data->head, ray, 0.001, INFINITY, &record)) {
    direct_light = init_color(0, 0, 0);
    if (record.material.type == MAT_LAMBERTIAN ||
        record.material.type == MAT_METAL)
      direct_light =
          calculate_direct_lighting(&record, &data->head, &data->light, ray);
    indirect_light =
        calculate_indirect_lighting(record, state, ray, num_recursions, data);
    ambient_effect = scale_vec3(data->ambient.color, data->ambient.ratio);
    final_ambient = multiply_vec3(record.material.albedo, ambient_effect);
    return (clamp_color(
        add_triple_vec3(direct_light, indirect_light, final_ambient)));
  }
  return (calculate_background_color(ray));
}

int render(t_program *data) {
  if (data->window == NULL)
    return (EXIT_SUCCESS);

  t_xorshift64_state state;
  init_xorshift64_state(&state);
  generate_random_scene(&data->head, &state);

  printf("Rendering started\n");
  clock_t begin = clock();
  const int max_recursions = 50;
  const int num_samples_per_pixel = 100;
  for (int y = 0; y < HEIGHT; y++) {
    printf("Scanlines reamaining: %d\n", HEIGHT - y);
    for (int x = 0; x < WIDTH; x++) {

      t_color pixel_color = init_color(0, 0, 0);
      for (int sample = 0; sample < num_samples_per_pixel; sample++) {
        double x_offset = (x + random_double(&state)) / (WIDTH - 1);
        double y_offset = (y + random_double(&state)) / (HEIGHT - 1);
        t_ray ray = get_ray(data->camera, x_offset, y_offset);
        pixel_color = add_vec3(
            pixel_color, calculate_color(ray, data, &state, max_recursions));
      }
      pixel_color = divide_vec3(pixel_color, num_samples_per_pixel);
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

int main(int argc, char *argv[]) {
  t_program data;
  parse(argc, argv, &data);
  init_mlx_resources(&data);
  set_mlx_hooks(&data);
  render(&data);
  mlx_loop(data.mlx);
  destroy_mlx_resources_if_allocated(&data);
  destroy_object_list(&data.head);
  return EXIT_SUCCESS;
}
