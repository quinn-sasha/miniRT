#ifndef SPHERE_H
#define SPHERE_H

#include "hit_record.h"
#include "vec3.h"

typedef struct s_sphere
{
	t_point3 center;
	double radius; //半径
	t_material material; //materialはレイが球に当たり散乱レイを計算するのに参照する
} t_sphere;

t_sphere init_sphere(t_point3 center, double radius, t_material material);

bool hit_object(
	const t_ray ray,
	double min_t,
	double max_t,
	t_hit_record *hit_rec,
	void	*object_ptr //sphereだけでないのも受け取る？
);

bool hit_sphere_impl(
	const t_ray ray,
	double min_t,
	double max_t,
	t_hit_record *hit_rec,
	const t_sphere *sphere // <-- const t_sphere * を受け取る
);

#endif
