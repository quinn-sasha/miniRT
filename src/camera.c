#include "camera.h"
#include "math_utils.h"
#include "random_number_generator.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>

t_screen init_screen(int width, int height) {
  t_screen screen;
  screen.width = width;
  screen.height = height;
  screen.aspect_ratio = (double)width / height;
  return screen;
}

static void set_viewport_width_height(double *width, double *height,
                                      double aspect_ratio, double hfov) {
  double theta = degrees_to_radians(hfov);
  double width_scaling = tan(theta / 2);
  *width = 2.0 * width_scaling;
  *height = *width / aspect_ratio;
}

static t_vec3 calculate_lower_left_corner(t_vec3 origin, t_vec3 horizontal,
                                          t_vec3 vertical, t_vec3 w,
                                          double focus_distance) {
  t_vec3 minus_half_horizontal = inverse_vec3(divide_vec3(horizontal, 2));
  t_vec3 minus_half_vertical = inverse_vec3(divide_vec3(vertical, 2));
  t_vec3 z_componet = scale_vec3(w, -focus_distance);
  return add_triple_vec3(origin, minus_half_horizontal,
                         add_vec3(minus_half_vertical, z_componet));
}

t_camera init_camera(t_vec3 look_from, t_vec3 look_at, t_vec3 view_up,
                     double aspect_ratio, double hfov, double aperture,
                     double focus_distance) {
  t_camera camera;
  camera.origin = look_from;

  double viewport_width;
  double viewport_height;
  set_viewport_width_height(&viewport_width, &viewport_height, aspect_ratio,
                            hfov);
  t_vec3 w = normalize_vec3(sub_vec3(look_from, look_at));
  camera.right_dir = normalize_vec3(cross_vec3(view_up, w));
  camera.above_dir = normalize_vec3(cross_vec3(w, camera.right_dir));
  camera.horizontal =
      scale_vec3(camera.right_dir, viewport_width * focus_distance);
  camera.vertical =
      scale_vec3(camera.above_dir, viewport_height * focus_distance);
  camera.lower_left_corner = calculate_lower_left_corner(
      look_from, camera.horizontal, camera.vertical, w, focus_distance);
  camera.lens_radius = aperture / 2;
  return camera;
}

t_ray get_ray(t_camera camera, double x_offset, double y_offset,
              t_xorshift64_state *state) {
  t_vec3 pos_in_circle =
      scale_vec3(init_random_vec3_in_unit_circle(state), camera.lens_radius);
  t_vec3 origin_offset =
      add_vec3(scale_vec3(camera.right_dir, pos_in_circle.x),
               scale_vec3(camera.above_dir, pos_in_circle.y));
  t_vec3 ray_origin = add_vec3(camera.origin, origin_offset);
  t_vec3 offset_from_lower_left = add_triple_vec3(
      camera.lower_left_corner, scale_vec3(camera.horizontal, x_offset),
      scale_vec3(camera.vertical, y_offset));
  t_ray ray =
      init_ray(ray_origin, sub_vec3(offset_from_lower_left, ray_origin));
  return ray;
}
