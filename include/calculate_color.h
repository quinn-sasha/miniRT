/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_color.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 19:06:17 by ikota             #+#    #+#             */
/*   Updated: 2025/12/26 19:06:18 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULATE_COLOR_H
# define CALCULATE_COLOR_H

# include "color.h"
# include "hit_record.h"
# include "light.h"
# include "minirt.h"
# include "object_list.h"
# include "vec3.h"

t_vec3	calculate_diffuse(t_light *light, t_hit_record *record,
			t_vec3 normalized_light_dir_vec);
t_vec3	calculate_specular(t_hit_record *record, t_light *light, t_ray ray,
			t_vec3 normalized_light_dir_vec);
t_color	calculate_diffuse_specular(t_program *data, t_hit_record *record,
			t_vec3 normalized_light_dir_vec, t_ray ray);

t_color	calculate_direct_lighting(t_hit_record *record, t_program *data,
			t_ray ray, t_range range);
t_color	calculate_indirect_lighting(t_hit_record record,
			t_xorshift64_state *state, t_ray ray, t_program *data);
t_color	calculate_background_color(t_ray ray);

t_color	calculate_color(t_ray ray, t_program *data, t_xorshift64_state *state,
			int num_recursions);

#endif
