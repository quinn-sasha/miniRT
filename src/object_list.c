#include "object_list.h"
#include "hit_record.h"
#include "sphere.h"
#include <stdio.h>
#include <stdlib.h>

void init_object_list(t_object_list *list) {
  list->head = malloc(sizeof(t_scence_object));
  list->head->next = NULL;
}

// Assume sphere was dynamically alocated
// TODO: 球以外のオブジェクトの削除方法を追加する
void free_scene_object(t_scence_object *object) {
  free(object->content.sphere);
  free(object);
}

// TODO: Error handling when tries to delete empty object
void object_list_destroy(t_object_list *list) {
  if (list->head->next == NULL) {
    free(list->head);
    return;
  }
  t_scence_object *node = list->head;
  while (node->next) {
    t_scence_object *next = node->next->next;
    free_scene_object(node->next);
    node->next = next;
  }
  free(list->head);
}

// Debug
void object_list_debug_print(t_object_list *list) {
  t_scence_object *node = list->head->next;
  if (node == NULL) {
    printf("List is empty\n");
    return;
  }
  while (node) {
    if (node->type == OBJ_SPHERE) {
      dprintf(2, "shpere ");
    }
    node = node->next;
  }
}

// TODO: memory error handling
t_scence_object *new_scene_object(void *object, e_object_type type) {
  t_scence_object *new_object = malloc(sizeof(t_scence_object));
  new_object->type = type;
  new_object->content.sphere = (t_sphere *)object;
  new_object->next = NULL;
  return new_object;
}

void object_list_insert_last_generic(t_object_list *list, void *object,
                                     e_object_type type) {
  t_scence_object *node = list->head;
  while (node->next) {
    node = node->next;
  }
  node->next = new_scene_object(object, type);
}

// TODO: 球以外のオブジェクトに対応する
void object_list_insert_sphere_last(t_object_list *list, t_sphere *sphere) {
  object_list_insert_last_generic(list, sphere, OBJ_SPHERE);
}

bool object_list_hits(t_object_list *list, t_ray ray, double min_t,
                      double max_t, t_hit_record *record) {
  t_hit_record temp_record;
  bool hits_anything = false;
  double closest_so_far = max_t;

  t_scence_object *object = list->head->next;
  while (object) {
    if (hits_sphere(ray, min_t, closest_so_far, &temp_record,
                    *object->content.sphere)) {
      hits_anything = true;
      closest_so_far = temp_record.t;
      *record = temp_record;
    }
    object = object->next;
  }
  return hits_anything;
}
