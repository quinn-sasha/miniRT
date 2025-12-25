#include "plane.h"
#include "hit_record.h"
#include "xmalloc.h"
#include <math.h>
#include <stdlib.h>

t_plane *new_plane(t_vec3 point, t_vec3 normal, t_material material) {
  t_plane *new_plane = xmalloc(sizeof(t_plane));
  new_plane->point = point;
  new_plane->normal = normalize_vec3(normal);
  new_plane->material = material;
  return (new_plane);
}

bool hits_plane(const t_ray ray, double min_t, double max_t,
                t_hit_record *record, t_plane *plane) {
  double denom = dot_vec3(ray.direction, plane->normal);

  if (fabs(denom) < 1e-6)
    return false;
  t_vec3 tmp = sub_vec3(plane->point, ray.origin);
  double numerator = dot_vec3(tmp, plane->normal);
  double t = numerator / denom;

  if (t < min_t || t > max_t)
    return false;
  record->t = t;
  record->intersection = ray_at(ray, t);

  set_fronts_face_and_normal_vector(record, ray, plane->normal);
  record->material = plane->material;
  return (true);
}
