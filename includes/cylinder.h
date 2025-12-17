#ifndef CYLINDER_H
#define CYLINDER_H

#include "object.h"

typedef struct s_cylinder
{
	t_point3 center;
	t_vec3 axis; //円柱が伸びる方向　軸
	double radius;
	double height;
	t_material material;
} t_cylinder;

t_cylinder init_cylinder(
	t_point3 center,
	t_vec3 axis,
	double radius,
	double height,
	t_material material
);

bool hit_cylinder(
	const t_ray ray,
	double min_t,
	double max_t,
	t_hit_record *hit_rec,
	const t_cylinder *cyl
);

#endif
