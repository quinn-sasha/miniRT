#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

#include "range.h"
#include "cylinder.h"
#include "plane.h"
#include "sphere.h"

typedef enum {
  OBJ_SPHERE,
  OBJ_PLANE,
  OBJ_CYLINDER,
} e_object_type;

typedef struct s_scene_object {
  e_object_type type;
  union u_data {
    t_sphere *sphere;
    t_plane *plane;
    t_cylinder *cylinder;
  } data;
  struct s_scene_object *next;
} t_scene_object;

void init_dummy_head(t_scene_object *head);
void destroy_scene_object(t_scene_object *object);
void destroy_object_list(t_scene_object *head);
t_scene_object *new_scene_object(void *object, e_object_type type);
void add_object_generic(t_scene_object *head, void *object, e_object_type type);
void add_sphere(t_scene_object *head, t_sphere *sphere);
void add_plane(t_scene_object *head, t_plane *plane);
void add_cylinder(t_scene_object *head, t_cylinder *cylinder);
bool hits_any_object(t_scene_object *head, t_ray ray, t_range range, t_hit_record *record);
int count_objects(t_scene_object *head);

#endif
