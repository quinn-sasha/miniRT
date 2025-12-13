#include "camera.h"
#include "ray.h"
#include "vec3.h"
#include "math_utils.h"

t_screen init_screen(int width, int height)
{
	t_screen screen;
  screen.width = width;
	screen.height = height;
	screen.aspect_ratio = (double)width / height;
	return (screen);
}

static void set_viewport_width_height(double *width, double *height,
                                      double aspect_ratio, double vfov)
{
  double theta = degrees_to_radians(vfov);
  double height_scaling = tan(theta / 2);
  *height = 2.0 * height_scaling;
  *width = *height * aspect_ratio;
}

static t_vec3 get_lower_left_corner(t_vec3 origin, t_vec3 horizontal,
                                    t_vec3 vertical, t_vec3 *w, double focus_distance)
{
  //ビューポートの左下隅(lower_left_corner)の座標計算
  // LLC = origin - horizontal / 2 - vertical / 2 - (0, 0, focal_length)
  t_vec3 minus_half_horizontal = vec3_mult_scalar(horizontal, 0.5);
  t_vec3 minus_half_vertical = vec3_mult_scalar(vertical, 0.5);
  t_vec3 z_component = vec3_mult_scalar(*w, focus_distance);

  t_point3  lower_left_corner = vec3_sub(origin, minus_half_horizontal);
            lower_left_corner = vec3_sub(lower_left_corner, minus_half_vertical);
            lower_left_corner = vec3_sub(lower_left_corner, z_component);
  return (lower_left_corner);
}

t_camera init_camera(t_vec3 look_from, t_vec3 look_at, t_vec3 view_up,
                      double aspect_ratio, double vfov, double aperture, double focus_distance) {
  t_camera camera;
  camera.origin = look_from;

  double viewport_width;
  double viewport_height;
  set_viewport_width_height(&viewport_width, &viewport_height, aspect_ratio, vfov);

  t_vec3 w = vec3_unit_vector(vec3_sub(look_from, look_at));
  camera.right_dir = vec3_unit_vector(vec3_cross(view_up, w));
  camera.above_dir = vec3_unit_vector(vec3_cross(w, camera.right_dir));
  camera.horizontal = vec3_mult_scalar(camera.right_dir, viewport_width);
  camera.vertical = vec3_mult_scalar(camera.above_dir, viewport_height);
  camera.lower_left_corner = get_lower_left_corner(
      look_from, camera.horizontal, camera.vertical, &w, focus_distance);
  camera.lens_radius = aperture / 2;
  return camera;
}

//正規化座標からレイを生成する関数
t_ray get_ray(t_camera camera, double x_offset, double y_offset, t_xorshift64_state *state)
{
  t_vec3 pos_in_circle = vec3_mult_scalar(get_random_vec3_in_unit_circle(state), camera.lens_radius);
  t_vec3 origin_offset = vec3_add(
              vec3_mult_scalar(camera.right_dir, pos_in_circle.x),
              vec3_mult_scalar(camera.above_dir, pos_in_circle.y));
  t_vec3 ray_origin = vec3_add(camera.origin, origin_offset);
  t_vec3 offset_from_lower_left = vec3_add_triple(camera.lower_left_corner,
                                vec3_mult_scalar(camera.horizontal, x_offset),
                                vec3_mult_scalar(camera.vertical, y_offset));
  // //レイの方向ベクトルを計算
  // //direction = lower_left_corner + u*horizontal + v*vertical - origin
  // t_vec3 scaled_h = vec3_mult_scalar(camera.horizontal, x_offset);
  // t_vec3 scaled_v = vec3_mult_scalar(camera.vertical, y_offset);

  // t_vec3  view_point = vec3_add(camera.lower_left_corner, scaled_h);
  //         view_point = vec3_add(view_point, scaled_v);
  // // 2. レイの方向ベクトルを計算: Direction = P - Origin
  // // (このケースでは Origin が (0,0,0) なので view_point そのものだが、将来の拡張のために vec3_sub を使う)
  t_vec3 direction = vec3_sub(offset_from_lower_left, ray_origin);

  // 3.レイを生成し返す
  return (init_ray(ray_origin, direction));
}
