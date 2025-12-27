/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:06:20 by ikota             #+#    #+#             */
/*   Updated: 2025/12/27 14:34:57 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "error_utils.h"
#include "plane.h"
#include "sphere.h"
#include "xmalloc.h"
#include <stdio.h>

t_scene_object	*new_scene_object(void *object, t_object_type type)
{
	t_scene_object	*new_object;

	new_object = xmalloc(sizeof(t_scene_object));
	new_object->type = type;
	new_object->next = NULL;
	if (type == OBJ_SPHERE)
		new_object->data.sphere = (t_sphere *)object;
	else if (type == OBJ_PLANE)
		new_object->data.plane = (t_plane *)object;
	else if (type == OBJ_CYLINDER)
		new_object->data.cylinder = (t_cylinder *)object;
	else
		error_exit("new_scene_object(): Unknown object type");
	return (new_object);
}

void	add_object_generic(t_scene_object *head, void *object,
		t_object_type type)
{
	t_scene_object	*node;

	node = head;
	while (node->next)
	{
		node = node->next;
	}
	node->next = new_scene_object(object, type);
}

void	add_sphere(t_scene_object *head, t_sphere *sphere)
{
	add_object_generic(head, sphere, OBJ_SPHERE);
}

void	add_plane(t_scene_object *head, t_plane *plane)
{
	add_object_generic(head, plane, OBJ_PLANE);
}

void	add_cylinder(t_scene_object *head, t_cylinder *cylinder)
{
	add_object_generic(head, cylinder, OBJ_CYLINDER);
}
