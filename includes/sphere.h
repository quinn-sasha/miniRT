#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

typedef struct s_sphere
{
	t_point3 center;
	double radius; //半径
} t_sphere;

t_sphere sphere_new(t_point3 cen, double r);

bool hit_sphere(
	const t_ray r,
	double t_min,
	double t_max,
	t_hit_record *rec,
	const t_sphere *sp //球の情報（center, radius）へのポインタ
);

#endif
