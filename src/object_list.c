/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:15:48 by ikota             #+#    #+#             */
/*   Updated: 2025/12/26 15:15:49 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_utils.h"
#include "hit_record.h"
#include "range.h"
#include "xmalloc.h"
#include <stdio.h>
#include <stdlib.h>

void	init_dummy_head(t_scene_object *head)
{
	head->next = NULL;
}

static bool	hits_object(t_ray ray, t_range range, t_hit_record *record,
		t_scene_object *object)
{
	if (object->type == OBJ_SPHERE)
	{
		return (hits_sphere(ray, range, record, *object->data.sphere));
	}
	if (object->type == OBJ_PLANE)
	{
		return (hits_plane(ray, range, record, object->data.plane));
	}
	if (object->type == OBJ_CYLINDER)
	{
		return (hit_cylinder(ray, range, record, object->data.cylinder));
	}
	print_error("hits_object(): Unknown object type");
	return (false);
}

bool	hits_any_object(t_scene_object *head, t_ray ray, t_range range,
		t_hit_record *record)
{
	t_hit_record	temp_record;
	bool			hits_anything;
	t_scene_object	*object;

	hits_anything = false;
	object = head->next;
	while (object)
	{
		if (hits_object(ray, range, &temp_record, object))
		{
			hits_anything = true;
			range.max_t = temp_record.t;
			*record = temp_record;
		}
		object = object->next;
	}
	return (hits_anything);
}

int	count_objects(t_scene_object *head)
{
	int				result;
	t_scene_object	*node;

	if (!head->next)
		return (0);
	result = 0;
	node = head->next;
	while (node)
	{
		result++;
		node = node->next;
	}
	return (result);
}
