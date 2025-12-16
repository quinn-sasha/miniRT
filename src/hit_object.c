#include "object.h"

bool hit_object(
    const t_ray ray,
    double min_t,
    double max_t,
    t_hit_record *hit_rec,
		void *object_ptr
)
{
	t_object *object = (t_object *)object_ptr; // void * を受け取る
  if (object->type == SPHERE)
		return	hit_sphere(ray, min_t, max_t, hit_rec, (t_sphere *)object->object_ptr);
	else if (object->type == PLANE)
		return hit_plane(ray, min_t, max_t, hit_rec, (t_plane *)object->object_ptr);
	return false;
		// else if (object_ptr->type == CYLINDER)
	// 	return hit_cylinder(ray, min_t, max_t, hit_rec, (t_cylinder *)object_ptr->ptr);
}
