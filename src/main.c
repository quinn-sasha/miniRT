#include "camera.h"
#include "color.h"
#include "hit_record.h"
#include "object_list.h"
#include "random_number_generator.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static t_color get_ray_color(t_ray ray, t_object_list *list) {
  t_hit_record hit_record;
  if (object_list_hits(list, ray, 0, INFINITY, &hit_record)) {
    t_vec3 normal = hit_record.normal_vector;
    t_color noraml_vector_color = init_color(normal.x, normal.y, normal.z);
    return scale_color(add_color(noraml_vector_color, init_color(1, 1, 1)),
                       0.5);
  }
  t_vec3 unit_direction = vec3_normalize(ray.direction);
  double t = 0.5 * (unit_direction.y + 1.0);
  t_color white = init_color(1.0, 1.0, 1.0);
  return add_color(scale_color(white, (1.0 - t)),
                   scale_color(init_color(0.5, 0.7, 1.0), t));
}

int main(void) {
  const double aspect_ratio = (double)16 / 9; // wdith / hieght
  const int image_width = 384;
  const int image_height = image_width / aspect_ratio;

  int fd = STDOUT_FILENO;
  dprintf(fd, "P3\n");
  dprintf(fd, "%d %d\n255\n", image_width, image_height);

  t_viewport viewport = init_viewport(aspect_ratio, 2.0 * aspect_ratio, 2.0);
  t_camera camera = init_camera(viewport, vec3_init(0, 0, 0), 1.0);

  t_object_list object_list;
  init_object_list(&object_list);
  object_list_insert_sphere_last(&object_list,
                                 new_sphere(vec3_init(0, 0, -1), 0.5));
  object_list_insert_sphere_last(&object_list,
                                 new_sphere(vec3_init(0, -100.5, -1), 100));

  const int num_samples_per_pixel = 100;
  t_xorshift64_state state;
  init_xorshift64_state(&state);
  for (int col = image_height - 1; col >= 0; col--) {
    for (int row = 0; row < image_width; row++) {
      dprintf(STDERR_FILENO, "Scanlines remaining: %d ", col);

      t_color pixel_color = init_color(0, 0, 0);
      for (int sample = 0; sample < num_samples_per_pixel; sample++) {
        double x_offset = (row + random_double(&state)) / (image_width - 1);
        double y_offset = (col + random_double(&state)) / (image_height - 1);
        t_ray ray = get_ray(camera, x_offset, y_offset);
        pixel_color = add_color(pixel_color, get_ray_color(ray, &object_list));
      }
      write_color(fd, pixel_color, num_samples_per_pixel);
    }
  }
  dprintf(STDERR_FILENO, "Done\n");
}
