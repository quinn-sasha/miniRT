#ifndef CALCULATE_COLOR_H
# define CALCULATE_COLOR_H

#include "vec3.h"
#include "color.h"
#include "hit_record.h"
#include "light.h"
#include "object_list.h"
#include "minirt.h"

t_color	calculate_direct_lighting(t_hit_record *record,
		t_scene_object *head, t_light *light, t_ray ray);

t_color	calculate_indirect_lighting(t_hit_record record,
		t_xorshift64_state *state, t_ray ray, int num_recursions,
		t_program *data);
t_color calculate_background_color(t_ray ray);

#endif
