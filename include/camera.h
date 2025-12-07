#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
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

t_viewport init_viewport(double aspect_ratio, double width, double height);
t_camera init_camera(t_viewport viewport, t_vec3 origin, double focal_legth);
t_ray get_ray(t_camera camera, double x_offset, double y_offset);

#endif // !CAMERA_H
