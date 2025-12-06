#include "camera.h"
#include "ray.h"

// TODO: 引数の渡し方がまだ完全に決まっていない
t_viewport init_viewport(double aspect_ratio, double width, double height) {
  t_viewport viewport;
  viewport.aspect_ratio = aspect_ratio;
  viewport.width = width;
  viewport.height = height;
  return viewport;
}

static t_vec3 get_lower_left_corner(t_vec3 origin, t_vec3 horizontal,
                                    t_vec3 vertical, double focal_length) {
  t_vec3 minus_half_horizontal = vec3_inverse(vec3_divide(horizontal, 2));
  t_vec3 minus_half_vertical = vec3_inverse(vec3_divide(vertical, 2));
  t_vec3 minus_z_componet = vec3_inverse(vec3_init(0, 0, focal_length));
  return vec3_add_triple(origin, minus_half_horizontal,
                         vec3_add(minus_half_vertical, minus_z_componet));
}

t_camera init_camera(t_viewport viewport, t_vec3 origin, double focal_legth) {
  t_camera camera;
  camera.origin = origin;
  camera.focal_length = focal_legth;
  camera.horizontal = vec3_init(viewport.width, 0, 0);
  camera.vertical = vec3_init(0, viewport.height, 0);
  camera.lower_left_corner = get_lower_left_corner(
      origin, camera.horizontal, camera.vertical, focal_legth);
  return camera;
}

t_ray get_ray(t_camera camera, double x_offset, double y_offset) {
  t_vec3 offset_from_lower_left = vec3_add_triple(
      camera.lower_left_corner, vec3_scale(camera.horizontal, x_offset),
      vec3_scale(camera.vertical, y_offset));
  t_ray ray =
      init_ray(camera.origin, vec3_sub(offset_from_lower_left, camera.origin));
  return ray;
}
