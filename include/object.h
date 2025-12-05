#ifndef OBJECT_H
#define OBJECT_H

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

#endif
