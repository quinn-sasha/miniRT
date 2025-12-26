#include "hit_record.h"
#include "range.h"
#include "sphere.h"
#include "vec3.h"
#include "xmalloc.h"
#include <math.h>
#include <stdlib.h>

t_sphere	*new_sphere(t_vec3 center, double radius, t_material material)
{
	t_sphere	*new_sphere;

	new_sphere = xmalloc(sizeof(t_sphere));
	new_sphere->center = center;
	new_sphere->radius = radius;
	new_sphere->material = material;
	return (new_sphere);
}

// TODO: 他の衝突判定関数に合わせて、t_sphere型からt_sphere *型にする
bool	hits_sphere(t_ray ray, t_range range, t_hit_record *record,
		t_sphere sphere)
{
	t_vec3	sphere2camera;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	double	smaller_t;
	double	bigger_t;
	t_vec3	outward_normal_vector;

	sphere2camera = sub_vec3(ray.origin, sphere.center);
	a = length_squared_vec3(ray.direction);
	half_b = dot_vec3(sphere2camera, ray.direction);
	c = length_squared_vec3(sphere2camera) - sphere.radius * sphere.radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (false);
	smaller_t = (-half_b - sqrt(discriminant)) / a;
	bigger_t = (-half_b + sqrt(discriminant)) / a;
	if (smaller_t > range.min_t && smaller_t < range.max_t)
		record->t = smaller_t;
	else if (bigger_t > range.min_t && bigger_t < range.max_t)
		record->t = bigger_t;
	else
		return (false);
	record->intersection = ray_at(ray, record->t);
	outward_normal_vector = divide_vec3(sub_vec3(record->intersection,
				sphere.center), sphere.radius);
	set_fronts_face_and_normal_vector(record, ray, outward_normal_vector);
	record->material = sphere.material;
	return (true);
}
