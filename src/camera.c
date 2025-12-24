#include "camera.h"
#include "math_utils.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>

static void set_viewport_width_height(double *width, double *height,
                                      double aspect_ratio, double hfov) {
  double theta = degrees_to_radians(hfov);
  double width_scaling = tan(theta / 2);
  *width = 2.0 * width_scaling;
  *height = *width / aspect_ratio;
}

static t_vec3 calculate_top_left_corner(t_vec3 origin, t_vec3 horizontal,
                                        t_vec3 down_vertical, t_vec3 back_dir,
                                        double focal_length) {
  t_vec3 half_horizontal = divide_vec3(horizontal, 2);
  t_vec3 half_vertical = divide_vec3(down_vertical, -2);
  t_vec3 z_componet =
      scale_vec3(back_dir, -focal_length); // modify back_dir to lookat_dir

  t_vec3 result = sub_vec3(origin, half_horizontal);
  result = add_vec3(result, half_vertical);
  result = add_vec3(result, z_componet);
  return result;
}

t_camera init_camera(t_vec3 look_from, t_vec3 look_at, t_vec3 view_up,
                     double aspect_ratio, double hfov, double focal_length) {
  t_camera camera;
  camera.origin = look_from;

  double viewport_width;
  double viewport_height;

  set_viewport_width_height(&viewport_width, &viewport_height, aspect_ratio,
                            hfov);
  t_vec3 back_dir = normalize_vec3(sub_vec3(look_from, look_at)); // modify
  camera.right_dir = normalize_vec3(cross_vec3(view_up, back_dir));
  camera.down_dir = normalize_vec3(cross_vec3(camera.right_dir, back_dir));
  camera.horizontal = scale_vec3(camera.right_dir, viewport_width);
  camera.vertical = scale_vec3(camera.down_dir, viewport_height);
  camera.top_left_corner = calculate_top_left_corner(
      look_from, camera.horizontal, camera.vertical, back_dir, focal_length);
  return camera;
}

t_ray get_ray(t_camera camera, double x_offset, double y_offset) {
  t_vec3 offset_from_top_left = add_triple_vec3(
      camera.top_left_corner, scale_vec3(camera.horizontal, x_offset),
      scale_vec3(camera.vertical, y_offset));
  t_ray ray =
      init_ray(camera.origin, sub_vec3(offset_from_top_left, camera.origin));
  return ray;
}
