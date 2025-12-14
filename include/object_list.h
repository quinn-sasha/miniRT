#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

#include "sphere.h"

typedef enum {
  OBJ_SPHERE,
} e_object_type;

typedef struct s_scene_object {
  e_object_type type;
  union u_data {
    t_sphere *sphere;
  } data;
  struct s_scene_object *next;
} t_scence_object;

void init_dummy_head(t_scence_object *head);
void destroy_scene_object(t_scence_object *object);
void destroy_object_list(t_scence_object *head);
t_scence_object *new_scene_object(void *object, e_object_type type);
void add_object_generic(t_scence_object *head, void *object,
                        e_object_type type);
void add_sphere(t_scence_object *head, t_sphere *sphere);
bool hits_any_object(t_scence_object *head, t_ray ray, double min_t,
                     double max_t, t_hit_record *record);

#endif
