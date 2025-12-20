#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include "hit_record.h"

typedef struct s_ambient
{
	double ratio;
	t_color color;
}	t_ambient;

//ambient_color = A_ratio * A_color * Material_albedo
t_ambient init_ambient_light(double ratio, double r, double g, double b);
t_vec3 calculate_shading(t_ambient ambient, t_hit_record rec);

#endif
