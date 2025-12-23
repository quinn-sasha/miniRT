#include "color.h"
#include "minirt.h"
#include "light.h"

void init_light(t_light *light)
{
	light->pos = init_vec3(0.0, 100.0, 0.0);
	light->brightness_ratio = 0.7;
	light->color = init_color(1.0, 1.0, 1.0);
}

void init_ambient(t_ambient *ambient){
	ambient->color = init_vec3(1.0, 1.0, 1.0);
	ambient->ratio = 0.2;
}
