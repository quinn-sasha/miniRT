#include "minirt.h"
#include "vector3.h"

void init_plane(t_plane plane, t_vector3 point, t_vector3 normal_vector) {
  plane.point = point;
  plane.normal_vector = normal_vector;
}

void init_sphere(t_sphere sphere, t_vector3 center, double radius) {
  sphere.center = center;
  sphere.radius = radius;
}

// TODO: 今のところただのベタ書き
void parse_objects(t_objects *dummy_head) {
  t_objects *objects = dummy_head;
  objects->next = malloc(sizeof(t_objects));
  objects = objects->next;
  objects->type = plane;
  // 平面が床にあるイメージ
  t_vector3 point = vec3_init(0, -2, 0);
  t_vector3 normal_vector = vec3_init(0, 1, 0);
  init_plane(objects->u_object.plane, point, normal_vector);
  // 正面にある球
  objects->next = malloc(sizeof(t_objects));
  objects = objects->next;
  objects->type = sphere;
  t_vector3 center = vec3_init(0, 0, -5);
  double radius = 1.0;
  init_sphere(objects->u_object.sphere, center, radius);
}

void init_data(t_data *data) {
  data->width = WINDOW_WIDTH;
  data->height = WINDOW_HEIGHT;
  parse_objects(data->dummy_head);
}

int main(void) {
  t_data data;
  init_data(&data);
  init_mlx_resources(&data);
  mlx_loop_hook(data.mlx, &simple_raytracing, &data);
  mlx_loop(data.mlx);
  free_mlx_resources_if_allocated(&data);
  return 0;
}
