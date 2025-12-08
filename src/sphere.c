#include "sphere.h"
#include "vec3.h"
#include <math.h>

//--初期化関数--

t_sphere sphere_new(t_point3 center, double radius)
{
	t_sphere sphere;
	sphere.center = center;
	sphere.radius = radius;
	return (sphere);
}

bool hit_sphere(
	const t_ray ray,
	double min_t,
	double max_t,
	t_hit_record *hit_rec,
	const t_sphere *sphere
)
{
    // 1.レイと球の中心を結ぶ　vec3 oc = r.origin() - center;
    t_vec3 oc = vec3_sub(ray.origin, sphere->center);

    // a = D・D (方向ベクトルの長さの二乗)
    double a = vec3_length_squared(ray.direction);

    // b = 2 * (D・OC)
    double half_b = vec3_dot(oc, ray.direction);

    // c = OC・OC - r^2
    double c = vec3_length_squared(oc) - sphere->radius * sphere->radius;

    // 判別式: discriminant = b^2 - 4ac
    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0.0)
        return (false);

		//解の計算
		double root = sqrt(discriminant);

		//カメラに近い方の交点
		double smaller_t = (-half_b - root) / a;
		double	bigger_t = (-half_b + root) / a;
		double t;

		if (smaller_t < max_t && smaller_t > min_t)
			t = smaller_t;
		else if (bigger_t > min_t && bigger_t < max_t)
			t = bigger_t;
		else
			return (false);
		hit_rec->t = t;
		//交点のベクトル
		hit_rec->intersection = ray_at(ray, t);
			//法線の計算
		t_vec3 outward_normal = vec3_div_scalar(vec3_sub(hit_rec->intersection, sphere->center), sphere->radius);

		//法線の向きを調整し、front_faceフラグを設定する。
		set_face_normal(ray, outward_normal, hit_rec);

		return (true);
}
