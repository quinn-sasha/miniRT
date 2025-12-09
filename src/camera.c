#include "camera.h"
#include "ray.h"

t_viewport init_viewport(double aspect_ratio, double width, double height)
{
	t_viewport viewport;
	viewport.aspect_ratio = aspect_ratio;
	viewport.width = width;
	viewport.height = height;
	return (viewport);
}

static t_vec3 get_lower_left_corner(t_vec3 origin, t_vec3 horizontal,
                                    t_vec3 vertical, double focal_length)
{
  //ビューポートの左下隅(lower_left_corner)の座標計算
  // LLC = origin - horizontal / 2 - vertical / 2 - (0, 0, focal_length)
  t_vec3 minus_half_horizontal = vec3_mult_scalar(horizontal, 0.5);
  t_vec3 minus_half_vertical = vec3_mult_scalar(vertical, 0.5);
  t_vec3 focus_vec = init_vec3(0, 0, focal_length);

  t_point3  lower_left_corner = vec3_sub(origin, minus_half_horizontal);
            lower_left_corner = vec3_sub(lower_left_corner, minus_half_vertical);
            lower_left_corner = vec3_sub(lower_left_corner, focus_vec);
  return (lower_left_corner);
}

t_camera init_camera(t_viewport viewport, t_vec3 origin, double focal_legth) {
  t_camera camera;
  camera.origin = origin;
  camera.focal_length = focal_legth;
  camera.horizontal = init_vec3(viewport.width, 0, 0);
  camera.vertical = init_vec3(0, viewport.height, 0);
  camera.lower_left_corner = get_lower_left_corner(
      origin, camera.horizontal, camera.vertical, focal_legth);
  return camera;
}
