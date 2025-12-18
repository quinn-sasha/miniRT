#include "sphere.h"
#include "vec3.h"
#include "object.h"
#include <math.h>
#include "cylinder.h"

//--初期化関数--

t_sphere init_sphere(t_point3 center, double radius, t_material material)
{
	t_sphere sphere;
	sphere.center = center;
	sphere.radius = radius;
	sphere.material = material;
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
    t_vec3 oc = sub_vec3(ray.origin, sphere->center);

    // a = D・D (方向ベクトルの長さの二乗)
    double a = length_squared_vec3(ray.direction);

    // b = 2 * (D・OC)
    double half_b = dot_vec3(oc, ray.direction);

    // c = OC・OC - r^2
    double c = length_squared_vec3(oc) - sphere->radius * sphere->radius;

		double t = solve_quadratic_t(a, half_b, c, min_t, max_t);
		hit_rec->t = t;
		//交点のベクトル
		hit_rec->intersection = ray_at(ray, t);
			//法線の計算
		t_vec3 outward_normal = div_scalar_vec3(sub_vec3(hit_rec->intersection, sphere->center), sphere->radius);

		//法線の向きを調整し、front_faceフラグを設定する。
		set_face_normal(ray, outward_normal, hit_rec);

		hit_rec->material = sphere->material;

		return (true);
}
