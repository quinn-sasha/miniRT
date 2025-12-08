#include "hittable.h"
#include "vec3.h"

// 法線の向きを調整し、front_faceフラグを設定する
void	set_face_normal(t_ray ray, t_vec3 outward_normal, t_hit_record *hit_rec)
{
	//レイの方向ベクトルと法線ベクトルの内積をチェックする
	//内積が負の場合、レイは物体の外側から当たっている (front_face = true).
	//内積が正の場合、レイは物体の内側から当たっている (front_face = false).
	hit_rec->front_face = (vec3_dot(ray.direction, outward_normal) < 0);

	//法線(rec->normal)を計算する
	//常にレイの衝突判定とは反対側に向くように法線を設定する
	if (hit_rec->front_face)
		//外側から当たった場合: そのままの外向き法線を使用
		hit_rec->normal_vector = outward_normal;
	else
		//内側から当たった場合: 法線の符号を反転して外向き（内側）法線とする
		hit_rec->normal_vector = vec3_neg(outward_normal);
}
