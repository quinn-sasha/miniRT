#include "color.h"
#include "hit_record.h"
#include "object_list.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static t_vec3 get_lower_left_corner(t_vec3 camera, t_vec3 horizontal,
                                    t_vec3 vertical, double focal_length) {
  t_vec3 minus_half_horizontal = vec3_inverse(vec3_divide(horizontal, 2));
  t_vec3 minus_half_vertical = vec3_inverse(vec3_divide(vertical, 2));
  t_vec3 minus_z_componet = vec3_inverse(vec3_init(0, 0, focal_length));
  return vec3_add_triple(camera, minus_half_horizontal,
                         vec3_add(minus_half_vertical, minus_z_componet));
}

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

  double viewport_height = 2.0;
  double viewport_width = viewport_height * aspect_ratio;
  double focal_length = 1.0;
  t_vec3 camera = vec3_init(0, 0, 0);
  t_vec3 horizontal = vec3_init(viewport_width, 0, 0);
  t_vec3 vertical = vec3_init(0, viewport_height, 0);
  t_vec3 lower_left_corner =
      get_lower_left_corner(camera, horizontal, vertical, focal_length);

  t_object_list object_list;
  init_object_list(&object_list);
  object_list_insert_sphere_last(&object_list,
                                 new_sphere(vec3_init(0, 0, -1), 0.5));
  object_list_insert_sphere_last(&object_list,
                                 new_sphere(vec3_init(0, -100.5, -1), 100));

  for (int col = image_height - 1; col >= 0; col--) {
    for (int row = 0; row < image_width; row++) {
      dprintf(STDERR_FILENO, "Scanlines remaining: %d ", col);

      double x_offset = (double)row / (image_width - 1);
      double y_offset = (double)col / (image_height - 1);
      t_vec3 offset_from_lower_left =
          vec3_add_triple(lower_left_corner, vec3_scale(horizontal, x_offset),
                          vec3_scale(vertical, y_offset));
      t_ray ray = init_ray(camera, vec3_sub(offset_from_lower_left, camera));
      t_color pixel_color = get_ray_color(ray, &object_list);
      write_color(fd, pixel_color);
    }
  }
  dprintf(STDERR_FILENO, "Done\n");
}
