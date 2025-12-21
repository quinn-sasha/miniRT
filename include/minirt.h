#include "camera.h"
#include "img.h"
#include "object_list.h"

#define WIDTH 1920
#define HEIGHT 1080

typedef struct s_program {
  void *mlx;
  void *window;
  t_img img;
  t_scene_object head;
  t_camera camera;
} t_program;
