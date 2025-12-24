#include "cylinder.h"
#include "hit_record.h"
#include "math_utils.h"
#include <stdlib.h>
#include <math.h>

t_cylinder *new_cylinder(
	t_vec3 center,
	t_vec3	axis,
	double radius,
	double height,
	t_material material
)
{
	t_cylinder *new_cylinder = malloc(sizeof(t_cylinder));
	new_cylinder->center = center;
	new_cylinder->axis = axis;
	new_cylinder->radius = radius;
	new_cylinder->height = height;
	new_cylinder->material = material;
	return new_cylinder;
}

static bool hit_cylinder_side(
	const t_ray ray,
	double min_t,
	double max_t,
	t_hit_record *record,
	const t_cylinder *cyl
)
{
  // 1.レイと中心を結ぶ　vec3 oc = r.origin() - center;
  t_vec3 oc = sub_vec3(ray.origin, cyl->center);

  // a = D・D (方向ベクトルの長さの二乗)
  double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;

  // b = 2 * (D・OC)
  double half_b = oc.x * ray.direction.x + oc.z * ray.direction.z;
  // c = OC・OC - r^2
  double c = oc.x * oc.x + oc.z * oc.z - cyl->radius * cyl->radius;
  // 判別式: discriminant = b^2 - 4ac
	// double t = solve_quadratic_t(a, half_b, c, min_t, max_t);
		// if (t == false)
		// return false;
	double discriminant = half_b * half_b - a * c;
  if (discriminant < 0)
    return false;
  double smaller_t = (-half_b - sqrt(discriminant)) / a;
  double bigger_t = (-half_b + sqrt(discriminant)) / a;
	double t;
  if (smaller_t > min_t && smaller_t < max_t)
    t = smaller_t;
  else if (bigger_t > min_t && bigger_t < max_t)
    t = bigger_t;
  else
    return false;
	// 高さの判定　Cy - h /2 <= Py <= Cy + h / 2
	t_vec3 intersection = ray_at(ray, t);
	double half_h = cyl->height / 2.0;
	if (intersection.y < - half_h || intersection.y > half_h)
		return false;

	//交点のベクトル
	record->t = t;
	record->intersection = intersection;
	//法線の計算　ｙ成分０
	t_vec3 outward_normal_vector = init_vec3(
		(record->intersection.x - cyl->center.x) / cyl->radius,
		0,
		(record->intersection.z - cyl->center.z) / cyl->radius
	);
	//法線の向きを調整し、front_faceフラグを設定する。
	set_fronts_face_and_normal_vector(record, ray, outward_normal_vector);
	record->material = cyl->material;
	return (true);
}

static bool hit_cylinder_cap(
	const t_ray ray,
	double min_t,
	double max_t,
	t_hit_record *record,
	const t_cylinder *cyl,
	double cap_height
)
{
	if (fabs(ray.direction.y) < 1e-6)
		return false;
	double t = (cap_height - ray.origin.y) / ray.direction.y;
	if (t < min_t || t > max_t)
		return false;
	t_vec3 intersection = ray_at(ray, t);
	double dx = intersection.x - cyl->center.x;
	double dz = intersection.z - cyl->center.z;
	//交点が中心軸から半径ｒ以内にあるかどうか
	if ((dx * dx + dz * dz) > cyl->radius * cyl->radius)
		return false;
	record->t = t;
	record->intersection = intersection;
	t_vec3 outward_normal_vector = init_vec3(0, 0, 0);
	if (cap_height > cyl->center.y)
		outward_normal_vector = init_vec3(0, 1.0, 0);
	else
		outward_normal_vector = init_vec3(0, -1.0, 0);
	set_fronts_face_and_normal_vector(record, ray, outward_normal_vector);
	record->material = cyl->material;
	return true;
}

static bool record_hit(bool *hit_anything, double *closest_so_far, t_hit_record *record)
{
	*hit_anything = true;
	*closest_so_far = record->t;
	return true;
}

static t_ray world_to_local_ray(t_ray ray, t_vec3 center, t_vec3 ex, t_vec3 ey, t_vec3 ez)
{
	//ワールド空間のレイをローカル空間に変換
	t_vec3 origin_diff = sub_vec3(ray.origin, center);
	t_ray 	local_ray;

	//平行移動後の座標と各基底ベクトルとの内積をとる
	local_ray.origin = init_vec3(
		dot_vec3(origin_diff, ex), //円柱の中心から見たレイの始点がex軸にどれだけ進んでいるか
		dot_vec3(origin_diff, ey),
		dot_vec3(origin_diff, ez)
	);

	local_ray.direction = init_vec3(
    dot_vec3(ray.direction, ex),
    dot_vec3(ray.direction, ey),
    dot_vec3(ray.direction, ez)
  );
	return local_ray;
}

static bool hit_cylinder_side_cap(
	t_ray local_ray,
	double min_t,
	double max_t,
	t_hit_record *record,
	const t_cylinder *cyl
)
{
	bool hit_anything = false;
	double  closest_so_far = max_t;
	t_cylinder local_cyl = *cyl;
	local_cyl.center = init_vec3(0, 0, 0);

	if (hit_cylinder_side(local_ray, min_t, closest_so_far, record, &local_cyl))
		hit_anything = record_hit(&hit_anything, &closest_so_far, record);
	//底面の判定
	if (hit_cylinder_cap(local_ray, min_t, closest_so_far, record, &local_cyl, - cyl->height / 2.0))
		hit_anything = record_hit(&hit_anything, &closest_so_far, record);
	//上面の判定
	if (hit_cylinder_cap(local_ray, min_t, closest_so_far, record, &local_cyl, cyl->height / 2.0))
		hit_anything = record_hit(&hit_anything, &closest_so_far, record);
	return hit_anything;
}

bool hit_cylinder(
	const t_ray ray,
	double min_t,
	double max_t,
	t_hit_record *record,
	const t_cylinder *cyl
)
{
	//ローカル基底ベクトルの作成
	t_vec3 ey = normalize_vec3(cyl->axis);
	t_vec3 tmp = init_vec3(0, 0, 0);
	if(fabs(ey.y) < 0.9) //ey と tmpのなす角が十分に離れていることを保証するため
		tmp =	init_vec3(0, 1, 0);
	else
		tmp = init_vec3(1, 0, 0);
	t_vec3 ex = normalize_vec3(cross_vec3(tmp, ey));
	t_vec3 ez = cross_vec3(ex, ey);

	t_ray local_ray = world_to_local_ray(ray, cyl->center, ex, ey, ez);

	if (!hit_cylinder_side_cap(local_ray, min_t, max_t, record, cyl))
		return false;
	//結果をワールド空間に戻す
	t_vec3 local_n = record->normal_vector;
	record->normal_vector = add_triple_vec3(
		scale_vec3(ex, local_n.x),
		scale_vec3(ey, local_n.y),
		scale_vec3(ez, local_n.z)
	);
	record->intersection = ray_at(ray, record->t);
	set_fronts_face_and_normal_vector(record, ray, record->normal_vector);
	return true;
}
// 平面の交差判定を円柱の半径ｒ以内の範囲に限定して行い、側面と蓋の衝突のうち
// 最も距離ｔが近いものを採用する
//　円柱を回転させるのではなくレイを逆方向に回転させる　その座標系で計算するのはもとの座標系でも同じ
// 円柱の向きを基準とした新しい座標系を作る
// 円柱の向きaxisを新しいｙ軸とする　これに直交するｘ軸とｚ軸を作れば座標変換できる
// 移動: レイの原点から円柱の中心を引く（円柱の中心を原点 0,0,0 とみなす）。
// 回転: レイの原点と方向ベクトルを、上で作った ex, ey, ez を使って「Y軸が円柱の軸」になるように変換する。
// 判定: 今持っている hit_cylinder_side と hit_cylinder_cap をそのまま使う！（これらはY軸平行を前提としているので、変換後のレイに対して正しく機能します）
// 復元: 衝突した後の「法線ベクトル」だけは、再び元の世界の向きに回転させて戻す。
