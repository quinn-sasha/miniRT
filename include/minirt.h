#ifndef MINIRT_H
#define MINIRT_H

#include "camera.h"
#include "img.h"
#include "light.h"
#include "object_list.h"
#include "light.h"

#define WIDTH 384
#define HEIGHT 216

typedef struct s_program {
  void *mlx;
  void *window;
  t_img img;
  t_scene_object head;
  t_camera camera;
  t_ambient ambient;
  t_light light;
} t_program;

#endif // !MINIRT_H
