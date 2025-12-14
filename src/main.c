#include "camera.h"
#include "color.h"
#include "hit_record.h"
#include "material.h"
#include "object_list.h"
#include "random_number_generator.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static t_object_list generate_random_scene(t_xorshift64_state *state) {
  t_object_list world;
  init_object_list(&world);
  t_material ground_material =
      init_lambertian_material(init_color(0.5, 0.5, 0.5));
  add_sphere(&world, new_sphere(init_vec3(0, -1000, 0), 1000, ground_material));

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
        add_sphere(&world, new_sphere(center, 0.2, sphere_material));
        continue;
      }
      if (material_decision < 0.95) {
        t_color albedo = init_random_vec3_range(state, 0.5, 1);
        double fuzziness = random_double_range(state, 0, 0.5);
        sphere_material = init_metal_material(albedo, fuzziness);
        add_sphere(&world, new_sphere(center, 0.2, sphere_material));
        continue;
      }
      sphere_material = init_dielectric_material(1.5); // glass: 1.5
      add_sphere(&world, new_sphere(center, 0.2, sphere_material));
    }
  }
  t_material material1 = init_dielectric_material(1.5);
  add_sphere(&world, new_sphere(init_vec3(0, 1, 0), 1.0, material1));
  t_material material2 = init_lambertian_material(init_color(0.4, 0.2, 0.1));
  add_sphere(&world, new_sphere(init_vec3(-4, 1, 0), 1.0, material2));
  t_material material3 = init_metal_material(init_color(0.7, 0.6, 0.5), 0.0);
  add_sphere(&world, new_sphere(init_vec3(4, 1, 0), 1.0, material3));
  return world;
}

static t_color calculate_color(t_ray ray, t_object_list *list,
                               t_xorshift64_state *state, int num_recursions) {
  if (num_recursions <= 0)
    return init_color(0, 0, 0);

  t_hit_record record;
  // Set t bigger than 0 to prevent shadow acne
  if (hits_any_object(list, ray, 0.001, INFINITY, &record)) {
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
      exit(EXIT_FAILURE); // TODO: print message to debug

    if (!return_value)
      return init_color(0, 0, 0);
    return multiply_vec3(
        calculate_color(scattered, list, state, num_recursions - 1),
        attenuation);
  }
  t_vec3 unit_direction = normalize_vec3(ray.direction);
  double t = 0.5 * (unit_direction.y + 1.0);
  t_color white = init_color(1.0, 1.0, 1.0);
  return add_vec3(scale_vec3(white, (1.0 - t)),
                  scale_vec3(init_color(0.5, 0.7, 1.0), t));
}

int main(void) {
  t_screen screen = init_screen(384, 216);
  t_vec3 lookfrom = init_vec3(13, 2, 3);
  t_vec3 lookat = init_vec3(0, 0, 0);
  t_vec3 view_up = init_vec3(0, 1, 0);
  double focus_dist = 10.0;
  t_camera camera = init_camera(lookfrom, lookat, view_up, screen.aspect_ratio,
                                45, 0.1, focus_dist);

  t_xorshift64_state state;
  init_xorshift64_state(&state);
  t_object_list world = generate_random_scene(&state);

  int fd = STDOUT_FILENO;
  dprintf(fd, "P3\n");
  dprintf(fd, "%d %d\n255\n", screen.width, screen.height);

  const int max_recursions = 50;
  const int num_samples_per_pixel = 100;
  for (int row = screen.height - 1; row >= 0; row--) {
    for (int col = 0; col < screen.width; col++) {
      dprintf(STDERR_FILENO, "Scanlines remaining: %d ", row);

      t_color pixel_color = init_color(0, 0, 0);
      for (int sample = 0; sample < num_samples_per_pixel; sample++) {
        double x_offset = (col + random_double(&state)) / (screen.width - 1);
        double y_offset = (row + random_double(&state)) / (screen.height - 1);
        t_ray ray = get_ray(camera, x_offset, y_offset, &state);
        pixel_color = add_vec3(
            pixel_color, calculate_color(ray, &world, &state, max_recursions));
      }
      write_color(fd, pixel_color, num_samples_per_pixel);
    }
  }
  dprintf(STDERR_FILENO, "Done\n");
}
