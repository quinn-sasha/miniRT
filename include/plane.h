#ifndef PLANE_H
#define PLANE_H

#include "range.h"
#include "vec3.h"
#include "material.h"

typedef struct s_plane
{
	t_vec3 point;
	t_vec3 normal;
	t_material material;
} t_plane;

t_plane *new_plane(t_vec3 point, t_vec3 normal, t_material material);
bool	hits_plane(
	t_ray ray,
	t_range range,
	t_hit_record *hit_rec,
	t_plane *plane_ptr
);

#endif
