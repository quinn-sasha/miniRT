#ifndef HIITABLE_H
#define HITTABLE_H

#include "ray.h"
#include <stdbool.h>

//レイと物体が交差したときに必要な全ての情報をまとめて記録するためのもの
typedef struct s_hit_record
{
	t_point3 intersection; //レイと物体が交差した交点の３次元

	t_vec3 normal_vector; //交点における物体の法線ベクトル

	double t; //ray parameter

	//法線がレイの内側を向いているか外側を向いているかを記録するフラグ
	bool	front_face;

} t_hit_record;

// t_ray ray : レイ
// double min_t : 許容される最初のt値
// double max_t : 許容される最大のt値
// t_hit_record *rec : 交差情報を書き込むためのポインタ
// void *object_ptr : 呼び出しもとの特定のオブジェクトへのポインタ
typedef bool (*t_hit_func)(const t_ray, double, double, t_hit_record *, void *);

//補助関数
//法線の向きを調整し、front_faceフラグを設定する
void set_face_normal(t_ray ray, t_vec3 outward_normal, t_hit_record *hit_rec);

#endif

//hittable シーン内の全物体をリストにまとめて保持し、
//各ピクセルから発射されたレイがどの物体に当たるかを一括で簡単にチェックできるようになる
//hit関数がレイとは別にt_min, t_maxという２つの値を受け取るのは有効な交点の探索範囲を制限するため
//原点と光源の間だけを探索するために制限
//最小距離 t_min = 0 にすればカメラの正面のみを考慮できる
//最大距離 t_max = ∞ 最も近い交点を見つけるため　最も近い物体があれば、遠い物体は無視したいからt_maxは動的に更新する
