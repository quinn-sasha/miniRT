#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

typedef struct s_camera {
  t_vec3 origin;
  t_vec3 horizontal;
  t_vec3 vertical;
  t_vec3 lower_left_corner;
  double focal_length;
} t_camera;

typedef struct s_viewport {
  double aspect_ratio;
  double width;
  double height;
} t_viewport;

#endif // !CAMERA_H
