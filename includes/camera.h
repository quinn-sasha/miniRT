#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

typedef struct s_camera
{
  t_vec3 origin;
  t_vec3 horizontal;
  t_vec3 vertical;
  t_vec3 right_dir;
  t_vec3 above_dir;
  t_vec3 lower_left_corner;
  double lens_radius;
} t_camera;

typedef struct s_screen
{
	int width;
	int height;
	double aspect_ratio;
}	t_screen;

t_screen	init_screen(int width, int height);
t_camera 	init_camera(t_vec3 look_from, t_vec3 look_at, t_vec3 view_up,
												double aspect_ratio, double hfov, double aperture, double focus_distance);
t_ray	get_ray(t_camera camera, double x_offset, double y_offset, t_xorshift64_state *state);

#endif
