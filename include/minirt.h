#ifndef MINIRT_H
#define MINIRT_H

#include "../libft/libft.h"
#include "color.h"
#include "hook_macros.h"
#include "mlx.h"
#include "vector3.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 300

enum e_object_type {
  plane,
  sphere,
  // cylinder,
};

typedef struct s_plane {
  t_vector3 point;
  t_vector3 normal_vector;
} t_plane;

typedef struct s_sphere {
  t_vector3 center;
  double radius;
} t_sphere;

typedef struct s_objects {
  enum e_object_type type; //現在u_objectのメモリに何が格納されているかを記録する
  union {
    t_plane plane;
    t_sphere sphere;
    // t_cylinder cylinder;
  } u_object; //平面と球体どちらかのデータを格納するための共通の箱
  struct s_objects *next; // NULL if there is no more object
} t_objects;

typedef struct s_data {
  void *mlx;
  void *window;
  int width;
  int height;
  t_objects *dummy_head;//シーン内のすべてのオブジェクトリストの先頭を指すポインタ
} t_data;

// minilibx_utils.c
void init_mlx_resources(t_data *data);
void init_mlx(t_data *data);
void free_mlx_resources_if_allocated(t_data *data);
// hook.c
int destroy_window(t_data *data);
int handle_keypress(int keysym, t_data *data);
// simple_raytracing.c
int simple_raytracing(t_data *data);

#endif
