#include "color.h"
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

double hit_sphere(t_vec3 center, double radius, t_ray ray) {
  t_vec3 center2origin = vec3_sub(ray.origin, center);
  double a = vec3_length_squared(ray.direction);
  double half_b = vec3_dot(center2origin, ray.direction);
  double c = vec3_length_squared(center2origin) - radius * radius;
  double discriminant = half_b * half_b - a * c;
  if (discriminant < 0)
    return -1.0;
  return (-half_b - sqrt(discriminant)) / a;
}

static t_color get_ray_color(t_ray ray) {
  t_vec3 center = vec3_init(0, 0, -1);
  double radius = 0.5;
  double t = hit_sphere(center, radius, ray);
  if (t > 0.0) {
    t_vec3 intersection = ray_at(ray, t);
    t_vec3 normal_vector = vec3_normalize(vec3_sub(intersection, center));
    return scale_color(init_color(normal_vector.x + 1, normal_vector.y + 1,
                                  normal_vector.z + 1),
                       0.5);
  }
  t_vec3 unit_direction = vec3_normalize(ray.direction);
  t = 0.5 * (unit_direction.y + 1.0);
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

  for (int col = image_height - 1; col >= 0; col--) {
    for (int row = 0; row < image_width; row++) {
      dprintf(STDERR_FILENO, "Scanlines remaining: %d ", col);

      double x_offset = (double)row / (image_width - 1);
      double y_offset = (double)col / (image_height - 1);
      t_vec3 offset_from_lower_left =
          vec3_add_triple(lower_left_corner, vec3_scale(horizontal, x_offset),
                          vec3_scale(vertical, y_offset));
      t_ray ray = init_ray(camera, vec3_sub(offset_from_lower_left, camera));
      t_color pixel_color = get_ray_color(ray);
      write_color(fd, pixel_color);
    }
  }
  dprintf(STDERR_FILENO, "Done\n");
}
