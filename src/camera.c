#include "camera.h"
#include "ray.h"
#include "vec3.h"

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

//正規化座標からレイを生成する関数
t_ray get_ray(t_camera camera, double x_offset, double y_offset)
{
  //レイの方向ベクトルを計算
  //direction = lower_left_corner + u*horizontal + v*vertical - origin
  t_vec3 scaled_h = vec3_mult_scalar(camera.horizontal, x_offset);
  t_vec3 scaled_v = vec3_mult_scalar(camera.vertical, y_offset);

  t_vec3  view_point = vec3_add(camera.lower_left_corner, scaled_h);
          view_point = vec3_add(view_point, scaled_v);
  // 2. レイの方向ベクトルを計算: Direction = P - Origin
  // (このケースでは Origin が (0,0,0) なので view_point そのものだが、将来の拡張のために vec3_sub を使う)
  t_vec3 direction = vec3_sub(view_point, camera.origin);

  // 3.レイを生成し返す
  return (init_ray(camera.origin, direction));
}
