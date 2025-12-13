#include "camera.h"
#include "color.h"
#include "hit_record.h"
#include "material.h"
#include "object_list.h"
#include "random_number_generator.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static t_color calculate_color(t_ray ray, t_object_list *list,
                               t_xorshift64_state *state, int num_recursions) {
  if (num_recursions <= 0)
    return init_color(0, 0, 0);

  t_hit_record record;
  // Set t bigger than 0 to prevent shadow acne
  if (object_list_hits(list, ray, 0.001, INFINITY, &record)) {
    t_color attenuation = record.material.albedo; // Assume attenuation = albedo
    t_ray scattered;
    bool return_value;
    if (record.material.type == MAT_LAMBERTIAN)
      return_value = lambertian_scatters(record, &scattered, state);
    else if (record.material.type == MAT_METAL)
      return_value = metal_scatters(ray, record, &scattered, state);
    else if (record.material.type == MAT_DIELECTRIC)
      return_value =
          dielectric_scatters(ray, record, &scattered, &attenuation, state);
    else
      exit(EXIT_FAILURE);

    if (!return_value)
      return init_color(0, 0, 0);
    return dot_color(
        calculate_color(scattered, list, state, num_recursions - 1),
        attenuation);
  }
  t_vec3 unit_direction = vec3_normalize(ray.direction);
  double t = 0.5 * (unit_direction.y + 1.0);
  t_color white = init_color(1.0, 1.0, 1.0);
  return add_color(scale_color(white, (1.0 - t)),
                   scale_color(init_color(0.5, 0.7, 1.0), t));
}

int main(void) {
  t_screen screen = init_screen(384, 216);
  t_vec3 lookfrom = vec3_init(3, 3, 2);
  t_vec3 lookat = vec3_init(0, 0, -1);
  t_vec3 view_up = vec3_init(0, 1, 0);
  double focus_dist = vec3_length(vec3_sub(lookat, lookfrom));
  t_camera camera = init_camera(lookfrom, lookat, view_up, screen.aspect_ratio,
                                45, 1.0, focus_dist);

  int fd = STDOUT_FILENO;
  dprintf(fd, "P3\n");
  dprintf(fd, "%d %d\n255\n", screen.width, screen.height);

  t_sphere *sphere1 =
      new_sphere(vec3_init(0, 0, -1), 0.5,
                 init_lambertian_material(init_color(0.1, 0.2, 0.5)));
  t_sphere *sphere2 =
      new_sphere(vec3_init(0, -100.5, -1), 100,
                 init_lambertian_material(init_color(0.8, 0.8, 0)));
  t_sphere *sphere3 =
      new_sphere(vec3_init(1, 0, -1), 0.5,
                 init_metal_material(init_color(0.8, 0.6, 0.2), 0.3));
  t_sphere *sphere4 =
      new_sphere(vec3_init(-1, 0, -1), 0.5, init_dielectric_material(1.5));
  t_sphere *sphere5 =
      new_sphere(vec3_init(-1, 0, -1), -0.45, init_dielectric_material(1.5));

  t_object_list object_list;
  init_object_list(&object_list);
  object_list_insert_sphere_last(&object_list, sphere1);
  object_list_insert_sphere_last(&object_list, sphere2);
  object_list_insert_sphere_last(&object_list, sphere3);
  object_list_insert_sphere_last(&object_list, sphere4);
  object_list_insert_sphere_last(&object_list, sphere5);

  const int max_recursions = 50;
  const int num_samples_per_pixel = 100;
  t_xorshift64_state state;
  init_xorshift64_state(&state);
  for (int col = screen.height - 1; col >= 0; col--) {
    for (int row = 0; row < screen.width; row++) {
      dprintf(STDERR_FILENO, "Scanlines remaining: %d ", col);

      t_color pixel_color = init_color(0, 0, 0);
      for (int sample = 0; sample < num_samples_per_pixel; sample++) {
        double x_offset = (row + random_double(&state)) / (screen.width - 1);
        double y_offset = (col + random_double(&state)) / (screen.height - 1);
        t_ray ray = get_ray(camera, x_offset, y_offset, &state);
        pixel_color =
            add_color(pixel_color, calculate_color(ray, &object_list, &state,
                                                   max_recursions));
      }
      write_color(fd, pixel_color, num_samples_per_pixel);
    }
  }
  dprintf(STDERR_FILENO, "Done\n");
}
