#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

#include "sphere.h"

typedef enum {
  OBJ_SPHERE,
} e_object_type;

typedef struct s_scene_object {
  e_object_type type;
  union u_content {
    t_sphere *sphere;
  } content;
  struct s_scene_object *next;
} t_scence_object;

typedef struct s_object_list {
  t_scence_object *head;
} t_object_list;

void init_object_list(t_object_list *list);
void free_scene_object(t_scence_object *object);
void object_list_destroy(t_object_list *list);
void object_list_debug_print(t_object_list *list);
t_scence_object *new_scene_object(void *object, e_object_type type);
void object_list_insert_last_generic(t_object_list *list, void *object,
                                     e_object_type type);
void object_list_insert_sphere_last(t_object_list *list, t_sphere *sphere);
bool object_list_hits(t_object_list *list, t_ray ray, double min_t,
                      double max_t, t_hit_record *record);

#endif
