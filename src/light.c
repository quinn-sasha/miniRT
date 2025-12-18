#include "light.h"
#include "hit_record.h"

t_ambient init_ambient_light(double ratio, double r, double g, double b)
{
	t_ambient ambient;
	ambient.ratio = ratio;
	ambient.color = init_vec3(r, g, b);
	return ambient;
}

t_vec3 calculate_shading(t_ambient ambient, t_hit_record rec)
{
	t_vec3 ambient_light = mult_scalar_vec3(ambient.color, ambient.ratio);

	t_vec3 final_color = mult_vec3(rec.material.albedo, ambient_light);

	return final_color;
}
