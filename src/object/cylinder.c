/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 20:28:16 by ikota             #+#    #+#             */
/*   Updated: 2025/12/26 17:03:43 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "hit_record.h"
#include "math_utils.h"
#include "range.h"
#include "xmalloc.h"
#include <math.h>
#include <stdlib.h>

t_cylinder *new_cylinder(t_vec3 center, t_vec3 axis, double radius,
                         double height, t_material material) {
  t_cylinder *new_cylinder;

  new_cylinder = xmalloc(sizeof(t_cylinder));
  new_cylinder->center = center;
  new_cylinder->axis = axis;
  new_cylinder->radius = radius;
  new_cylinder->height = height;
  new_cylinder->material = material;
  return (new_cylinder);
}

static bool hit_cylinder_side(const t_ray ray, t_range range,
                              t_hit_record *record, const t_cylinder *cyl) {
  t_quadratic quadratic;
  t_vec3 intersection;
  double half_h;
  t_vec3 outward_normal_vector;

  quadratic = prepare_quadratic_cylinder(ray, cyl);
  record->t = solve_quadratic_t(quadratic, range);
  if (record->t == false)
    return false;
  intersection = ray_at(ray, record->t);
  half_h = cyl->height / 2.0;
  if (intersection.y < -half_h || intersection.y > half_h)
    return (false);
  record->intersection = intersection;
  outward_normal_vector =
      init_vec3((record->intersection.x - cyl->center.x) / cyl->radius, 0,
                (record->intersection.z - cyl->center.z) / cyl->radius);
  set_fronts_face_and_normal_vector(record, ray, outward_normal_vector);
  record->material = cyl->material;
  return (true);
}

static bool hit_cylinder_cap(const t_ray ray, t_range range,
                             t_hit_record *record, const t_cylinder *cyl,
                             double cap_height) {
  double t;
  t_vec3 intersection;
  double dx;
  double dz;
  t_vec3 outward_normal_vector;

  if (fabs(ray.direction.y) < 1e-6)
    return (false);
  t = (cap_height - ray.origin.y) / ray.direction.y;
  if (t < range.min_t || t > range.max_t)
    return (false);
  intersection = ray_at(ray, t);
  dx = intersection.x - cyl->center.x;
  dz = intersection.z - cyl->center.z;
  // 交点が中心軸から半径ｒ以内にあるかどうか
  if ((dx * dx + dz * dz) > cyl->radius * cyl->radius)
    return (false);
  record->t = t;
  record->intersection = intersection;
  outward_normal_vector = init_vec3(0, 0, 0);
  if (cap_height > cyl->center.y)
    outward_normal_vector = init_vec3(0, 1.0, 0);
  else
    outward_normal_vector = init_vec3(0, -1.0, 0);
  set_fronts_face_and_normal_vector(record, ray, outward_normal_vector);
  record->material = cyl->material;
  return (true);
}

static bool record_hit(bool *hit_anything, double *closest_so_far,
                       t_hit_record *record) {
  *hit_anything = true;
  *closest_so_far = record->t;
  return (true);
}

static t_ray world_to_local_ray(t_ray ray, t_vec3 center, t_vec3 ex, t_vec3 ey,
                                t_vec3 ez) {
  t_vec3 origin_diff;
  t_ray local_ray;

  origin_diff = sub_vec3(ray.origin, center);
  local_ray.origin =
      init_vec3(dot_vec3(origin_diff, ex), dot_vec3(origin_diff, ey),
                dot_vec3(origin_diff, ez));
  local_ray.direction =
      init_vec3(dot_vec3(ray.direction, ex), dot_vec3(ray.direction, ey),
                dot_vec3(ray.direction, ez));
  return (local_ray);
}

static bool hit_cylinder_side_cap(t_ray local_ray, t_range range,
                                  t_hit_record *record, const t_cylinder *cyl) {
  bool hit_anything;
  double closest_so_far;
  t_cylinder local_cyl;

  hit_anything = false;
  local_cyl = *cyl;
  local_cyl.center = init_vec3(0, 0, 0);
  if (hit_cylinder_side(local_ray, range, record, &local_cyl))
    hit_anything = record_hit(&hit_anything, &closest_so_far, record);
  if (hit_cylinder_cap(local_ray, range, record, &local_cyl,
                       -cyl->height / 2.0))
    hit_anything = record_hit(&hit_anything, &closest_so_far, record);
  if (hit_cylinder_cap(local_ray, range, record, &local_cyl, cyl->height / 2.0))
    hit_anything = record_hit(&hit_anything, &closest_so_far, record);
  return (hit_anything);
}

bool hit_cylinder(const t_ray ray, t_range range, t_hit_record *record,
                  const t_cylinder *cyl) {
  t_vec3 ey;
  t_vec3 tmp;
  t_vec3 ex;
  t_vec3 ez;
  t_ray local_ray;
  t_vec3 local_n;

  // ローカル基底ベクトルの作成
  ey = normalize_vec3(cyl->axis);
  tmp = init_vec3(0, 0, 0);
  if (fabs(ey.y) < 0.9) // ey と tmpのなす角が十分に離れていることを保証するため
    tmp = init_vec3(0, 1, 0);
  else
    tmp = init_vec3(1, 0, 0);
  ex = normalize_vec3(cross_vec3(tmp, ey));
  ez = cross_vec3(ex, ey);
  local_ray = world_to_local_ray(ray, cyl->center, ex, ey, ez);
  if (!hit_cylinder_side_cap(local_ray, range, record, cyl))
    return (false);
  // 結果をワールド空間に戻す
  local_n = record->normal_vector;
  record->normal_vector =
      add_triple_vec3(scale_vec3(ex, local_n.x), scale_vec3(ey, local_n.y),
                      scale_vec3(ez, local_n.z));
  record->intersection = ray_at(ray, record->t);
  set_fronts_face_and_normal_vector(record, ray, record->normal_vector);
  return (true);
}
// 平面の交差判定を円柱の半径ｒ以内の範囲に限定して行い、側面と蓋の衝突のうち
// 最も距離ｔが近いものを採用する
// 　円柱を回転させるのではなくレイを逆方向に回転させる　その座標系で計算するのはもとの座標系でも同じ
// 円柱の向きを基準とした新しい座標系を作る
// 円柱の向きaxisを新しいｙ軸とする　これに直交するｘ軸とｚ軸を作れば座標変換できる
// 移動: レイの原点から円柱の中心を引く（円柱の中心を原点 0,0,0 とみなす）。
// 回転: レイの原点と方向ベクトルを、上で作った ex, ey, ez
// を使って「Y軸が円柱の軸」になるように変換する。 判定: 今持っている
// hit_cylinder_side と hit_cylinder_cap
// をそのまま使う！（これらはY軸平行を前提としているので、変換後のレイに対して正しく機能します）
// 復元:
// 衝突した後の「法線ベクトル」だけは、再び元の世界の向きに回転させて戻す。
