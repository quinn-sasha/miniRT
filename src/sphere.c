#include "sphere.h"
#include "vec3.h"
#include <math.h>

//--初期化関数--

t_sphere sphere_new(t_point3 cen, double r)
{
	t_sphere sp;
	sp.center = cen;
	sp.radius = r;
	return (sp);
}

bool hit_sphere(
	const t_ray r,
	double t_min,
	double t_max,
	t_hit_record *rec,
	const t_sphere *sp
)
{
    // 1.レイと球の中心を結ぶ　vec3 oc = r.origin() - center;
    t_vec3 oc = vec3_sub(r.origin, sp->center);

    // a = D・D (方向ベクトルの長さの二乗)
    double a = vec3_length_squared(r.direction);

    // b = 2 * (D・OC)
    double half_b = vec3_dot(oc, r.direction);

    // c = OC・OC - r^2
    double c = vec3_length_squared(oc) - sp->radius * sp->radius;

    // 判別式: discriminant = b^2 - 4ac
    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0.0)
        return (false);

		//解の計算
		double root = sqrt(discriminant);

		//カメラに近い方の交点
		double t_temp = (-half_b - root) / a;

		if (t_temp < t_max && t_temp > t_min)
		{
			rec->t = t_temp;
			rec->p = ray_at(r, rec->t);

			//法線の計算
			t_vec3 outward_normal = vec3_div_scalar(vec3_sub(rec->p, sp->center), sp->radius);

			//法線の向きを設定
			set_face_normal(r, outward_normal, rec);

			return (true);
		}
		// b) カメラから遠い方の交点をチェック (カメラに近い方が範囲外だった場合)
    // t_temp = (-half_b + root) / a
    t_temp = (-half_b + root) / a;
    if (t_temp < t_max && t_temp > t_min)
    {
        // 衝突情報を hit_record に記録
        rec->t = t_temp;
        rec->p = ray_at(r, rec->t);

        // 法線の計算: N = (P - C) / r
        t_vec3 outward_normal = vec3_div_scalar(vec3_sub(rec->p, sp->center), sp->radius);

        // 法線の向きを設定
        set_face_normal(r, outward_normal, rec);

        return (true); // 交差あり
    }
		//どちらの交点もt_min/t_maxの範囲外
		return (false);
}
