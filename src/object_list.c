#include "object_list.h"
#include "cylinder.h"
#include "error_utils.h"
#include "hit_record.h"
#include "plane.h"
#include "sphere.h"
#include <stdio.h>
#include <stdlib.h>

void init_dummy_head(t_scene_object *head) { head->next = NULL; }

void destroy_scene_object(t_scene_object *object) {
  if (object->type == OBJ_SPHERE) {
    free(object->data.sphere);
    free(object);
    return;
  }
  if (object->type == OBJ_PLANE) {
    free(object->data.plane);
    free(object);
    return;
  }
  if (object->type == OBJ_CYLINDER) {
    free(object->data.cylinder);
    free(object);
    return;
  }
  error_exit("destroy_scene_object(): Unknown object type");
}

// head は静的に割り当てられている
// TODO: Error handling when tries to delete empty object
void destroy_object_list(t_scene_object *head) {
  if (head->next == NULL)
    return;
  t_scene_object *node = head->next;
  while (node) {
    t_scene_object *to_free = node;
    node = node->next;
    destroy_scene_object(to_free);
  }
}

t_scene_object *new_scene_object(void *object, e_object_type type) {
  t_scene_object *new_object = malloc(sizeof(t_scene_object));
  new_object->type = type;
  new_object->next = NULL;
  if (type == OBJ_SPHERE)
    new_object->data.sphere = (t_sphere *)object;
  else if (type == OBJ_PLANE)
    new_object->data.plane = (t_plane *)object;
  else if (type == OBJ_CYLINDER)
    new_object->data.cylinder = (t_cylinder *)object;
  else
    error_exit("new_scene_object(): Unknown object type");
  return new_object;
}

void add_object_generic(t_scene_object *head, void *object,
                        e_object_type type) {
  t_scene_object *node = head;
  while (node->next) {
    node = node->next;
  }
  node->next = new_scene_object(object, type);
}

void add_sphere(t_scene_object *head, t_sphere *sphere) {
  add_object_generic(head, sphere, OBJ_SPHERE);
}

void add_plane(t_scene_object *head, t_plane *plane) {
  add_object_generic(head, plane, OBJ_PLANE);
}

void add_cylinder(t_scene_object *head, t_cylinder *cylinder) {
  add_object_generic(head, cylinder, OBJ_CYLINDER);
}

bool hits_object(t_ray ray, double min_t, double max_t, t_hit_record *record,
                 t_scene_object *object) {
  if (object->type == OBJ_SPHERE) {
    return hits_sphere(ray, min_t, max_t, record, *object->data.sphere);
  }
  if (object->type == OBJ_PLANE) {
    return hits_plane(ray, min_t, max_t, record, object->data.plane);
  }
  if (object->type == OBJ_CYLINDER) {
    return hit_cylinder(ray, min_t, max_t, record, object->data.cylinder);
  }
  print_error("hits_object(): Unknown object type");
  return false;
}

bool hits_any_object(t_scene_object *head, t_ray ray, double min_t,
                     double max_t, t_hit_record *record) {
  t_hit_record temp_record;
  bool hits_anything = false;
  double closest_so_far = max_t;

  t_scene_object *object = head->next;
  while (object) {
    if (hits_object(ray, min_t, closest_so_far, record, object)) {
      hits_anything = true;
      closest_so_far = temp_record.t;
      *record = temp_record;
    }
    object = object->next;
  }
  return hits_anything;
}

int count_objects(t_scene_object *head) {
  if (!head->next)
    return 0;

  int result = 0;
  t_scene_object *node = head->next;
  while (node) {
    result++;
    node = node->next;
  }
  return result;
}
