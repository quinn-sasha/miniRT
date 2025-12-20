#include "object_list.h"
#include "hit_record.h"
#include "sphere.h"
#include <stdio.h>
#include <stdlib.h>

void init_dummy_head(t_scene_object *head) { head->next = NULL; }

// TODO: 球以外のオブジェクトの削除方法を追加する
void destroy_scene_object(t_scene_object *object) {
  free(object->data.sphere);
  free(object);
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

// TODO: 球以外のオブジェクトに対応する
// TODO: memory error handling
t_scene_object *new_scene_object(void *object, e_object_type type) {
  t_scene_object *new_object = malloc(sizeof(t_scene_object));
  new_object->type = type;
  new_object->data.sphere = (t_sphere *)object;
  new_object->next = NULL;
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

// TODO: 球以外のオブジェクトに対応する
void add_sphere(t_scene_object *head, t_sphere *sphere) {
  add_object_generic(head, sphere, OBJ_SPHERE);
}

// TODO: 球以外のオブジェクトに対応する
bool hits_any_object(t_scene_object *head, t_ray ray, double min_t,
                     double max_t, t_hit_record *record) {
  t_hit_record temp_record;
  bool hits_anything = false;
  double closest_so_far = max_t;

  t_scene_object *object = head->next;
  while (object) {
    if (hits_sphere(ray, min_t, closest_so_far, &temp_record,
                    *object->data.sphere)) {
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
