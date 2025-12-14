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
                                    t_vec3 vertical, t_vec3 w, double focus_distance)
{
  //ビューポートの左下隅(lower_left_corner)の座標計算
  // LLC = origin - horizontal / 2 - vertical / 2 - (0, 0, focal_length)
  t_vec3 half_horizontal = mult_scalar_vec3(horizontal, 0.5);
  t_vec3 half_vertical = mult_scalar_vec3(vertical, 0.5);
  t_vec3 z_component = mult_scalar_vec3(w, focus_distance);

  t_point3  lower_left_corner = sub_vec3(origin, half_horizontal);
            lower_left_corner = sub_vec3(lower_left_corner, half_vertical);
            lower_left_corner = sub_vec3(lower_left_corner, z_component);
  return (lower_left_corner);
}

t_camera init_camera(t_vec3 look_from, t_vec3 look_at, t_vec3 view_up,
                      double aspect_ratio, double vfov, double aperture, double focus_distance) {
  t_camera camera;
  camera.origin = look_from;

  double viewport_width;
  double viewport_height;
  set_viewport_width_height(&viewport_width, &viewport_height, aspect_ratio, vfov);

  t_vec3 w = normalize_vec3(sub_vec3(look_from, look_at));
  camera.right_dir = normalize_vec3(cross_vec3(view_up, w));
  camera.above_dir = normalize_vec3(cross_vec3(w, camera.right_dir));
  camera.horizontal = mult_scalar_vec3(camera.right_dir, viewport_width * focus_distance);
  camera.vertical = mult_scalar_vec3(camera.above_dir, viewport_height * focus_distance);
  camera.lower_left_corner = get_lower_left_corner(
      look_from, camera.horizontal, camera.vertical, w, focus_distance);
  camera.lens_radius = aperture / 2;
  return camera;
}

//正規化座標からレイを生成する関数
t_ray get_ray(t_camera camera, double x_offset, double y_offset, t_xorshift64_state *state)
{
  t_vec3 pos_in_circle = mult_scalar_vec3(get_random_vec3_in_unit_circle(state), camera.lens_radius);
  t_vec3 origin_offset = add_vec3(
              mult_scalar_vec3(camera.right_dir, pos_in_circle.x),
              mult_scalar_vec3(camera.above_dir, pos_in_circle.y));
  t_vec3 ray_origin = add_vec3(camera.origin, origin_offset);
  t_vec3 offset_from_lower_left = add_triple_vec3(camera.lower_left_corner,
                                mult_scalar_vec3(camera.horizontal, x_offset),
                                mult_scalar_vec3(camera.vertical, y_offset));
  // //レイの方向ベクトルを計算
  // //direction = lower_left_corner + u*horizontal + v*vertical - origin
  // t_vec3 scaled_h = mult_scalar_vec3(camera.horizontal, x_offset);
  // t_vec3 scaled_v = mult_scalar_vec3(camera.vertical, y_offset);

  // t_vec3  view_point = add_vec3(camera.lower_left_corner, scaled_h);
  //         view_point = add_vec3(view_point, scaled_v);
  // // 2. レイの方向ベクトルを計算: Direction = P - Origin
  // // (このケースでは Origin が (0,0,0) なので view_point そのものだが、将来の拡張のために sub_vec3 を使う)
  t_vec3 direction = sub_vec3(offset_from_lower_left, ray_origin);

  // 3.レイを生成し返す
  return (init_ray(ray_origin, direction));
}
