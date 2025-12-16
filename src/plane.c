#include "plane.h"
#include "hit_record.h"

t_plane init_plane(t_point3 point, t_vec3 normal, t_material material)
{
	t_plane plane;
	plane.point = point;
	plane.normal = normalize_vec3(normal);
	plane.material = material;
	return (plane);
}

//(P - A)・N = 0   P：レイの点　A:平面上の点　N：平面の法線
// P(t) = Q + tD ｔが知りたい Q:rayの原点 D:rayの向き
//以下にｔの導出を示す。
// ((Q+tD) - A)・N = 0
// (Q - A)・N + (tD・N) = 0
// t(D・N) = -(Q - A)・N
// t(D・N) = (A - Q)・N
// t = (A - Q)・N / D・N

bool hit_plane(
	const t_ray ray,
	double min_t,
	double max_t,
	t_hit_record *hit_record,
	t_plane *plane
)
{
	//分母 (D ・ N)　denominator
	double denom = dot_vec3(ray.direction, plane->normal);
	//分母が０の場合、レイと平面は並行（衝突しない）
	if (fabs(denom) < 1e-6) //どれくらい小さい値と比較すべきか
		return false;
	//(A - Q) 平面上のレイの点 -　レイの原点　
	t_vec3 tmp = sub_vec3(plane->point, ray.origin);
	//分子(A - Q)・N
	double numerator = dot_vec3(tmp, plane->normal);
	//t 距離
	double t = numerator / denom;

	if (t < min_t || t > max_t)
		return false;
	hit_record->t = t;
	hit_record->intersection = ray_at(ray, t);

	set_face_normal(ray, plane->normal, hit_record);
	hit_record->material = plane->material;
	return (true);
}
