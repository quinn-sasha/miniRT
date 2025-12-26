/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list_destroy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:12:56 by ikota             #+#    #+#             */
/*   Updated: 2025/12/26 15:13:55 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "error_utils.h"
#include "hit_record.h"
#include "plane.h"
#include "range.h"
#include "sphere.h"
#include "xmalloc.h"
#include <stdio.h>
#include <stdlib.h>

void	destroy_scene_object(t_scene_object *object)
{
	if (object->type == OBJ_SPHERE)
	{
		free(object->data.sphere);
		free(object);
		return ;
	}
	if (object->type == OBJ_PLANE)
	{
		free(object->data.plane);
		free(object);
		return ;
	}
	if (object->type == OBJ_CYLINDER)
	{
		free(object->data.cylinder);
		free(object);
		return ;
	}
	error_exit("destroy_scene_object(): Unknown object type");
}

// head は静的に割り当てられている
void	destroy_object_list(t_scene_object *head)
{
	t_scene_object	*node;
	t_scene_object	*to_free;

	if (head->next == NULL)
		return ;
	node = head->next;
	while (node)
	{
		to_free = node;
		node = node->next;
		destroy_scene_object(to_free);
	}
}
