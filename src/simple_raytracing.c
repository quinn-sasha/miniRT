#include "minirt.h"
#include <stdlib.h>

/*
 * アスペクト比、FOV、カメラの移動・回転などは省略
 * 仮想スクリーンは(0, 0, 0)付近にあるという前提で書いている
 */

bool intersect_sphere(t_vector3 sphere_center, t_vector3 camera_vec,
                      t_vector3 screen_pos, double radius) {
  t_vector3 direction_vec = vec3_normalize(vec3_sub(screen_pos, camera_vec));
  t_vector3 sphere2camera = vec3_sub(camera_vec, sphere_center);
  double a = pow(vec3_length(direction_vec), 2);
  double b = 2 * vec3_dot(sphere2camera, direction_vec);
  double c = vec3_dot(sphere2camera, sphere2camera) - radius * radius;
  double d = b * b - 4 * a * c;
  if (d >= 0)
    return true;
  return false;
}

void reflect_aspect_ratio(double *screen_x, double *screen_y, t_data data) {
  if (data.width > data.height)
    *screen_x *= (double)data.width / data.height;
  else
    *screen_y *= (double)data.height / data.width;
}

int simple_raytracing(t_data data) {
  if (data.window == NULL)
    return EXIT_FAILURE;
  t_vector3 camera_vec = vec3_init(0, 0, -5);

  for (int x = 0; x < data.width; x++) {
    for (int y = 0; y < data.height; y++) {
      double screen_x = (x * 2.0 / data.width) - 1.0;
      double screen_y = 1.0 - (y * 2.0 / data.height);
      reflect_aspect_ratio(&screen_x, &screen_y, data);
      t_vector3 screen_position = vec3_init(screen_x, screen_y, 0);
      if (intersect_sphere(sphere_center, camera_vec, screen_position, radius))
        mlx_pixel_put(data.mlx, data.window, x, y, create_rgb(255, 0, 0));
      else
        mlx_pixel_put(data.mlx, data.window, x, y, create_rgb(255, 255, 255));
    }
  }
  return EXIT_SUCCESS;
}
