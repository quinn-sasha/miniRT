#ifndef PLANE_H
#define PLANE_H

#include "vec3.h"
#include "material.h"

typedef struct s_plane
{
	t_point3 point;
	t_vec3 normal;
	t_material material;
} t_plane;

t_plane init_plane(t_point3 point, t_vec3 normal, t_material material);
bool	hit_plane(
	t_ray ray,
	double min_t,
	double max_t,
	t_hit_record *hit_rec,
	t_plane *plane_ptr
);

#endif
