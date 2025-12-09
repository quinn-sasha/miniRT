#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

typedef struct s_camera
{
	t_point3 origin; //カメラの位置（視点）
	t_point3 lower_left_corner; //ビューポートの左下隅のワールド座標
	t_vec3	horizontal;  //ビューポートの水平方向ベクトル
	t_vec3	vertical; //ビューポートの垂直方向ベクトル
	double	focal_length;
} t_camera;

typedef struct s_viewport
{
	double aspect_ratio;
	double width;
	double height;
}	t_viewport;

t_viewport	init_viewport(double aspect_ratio, double width, double height);
t_camera 		init_camera(t_viewport viewport, t_vec3 origin, double focal_length);
t_ray	get_ray(t_camera camera, double x_offset, double y_offset);

#endif
