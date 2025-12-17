#ifndef OBJECT_H
#define OBJECT_H

#include <stdbool.h>
#include "sphere.h"
#include "plane.h"
#include "cylinder.h"

typedef enum e_type{
	SPHERE,
	PLANE,
	CYLINDER,
}t_type;

typedef struct s_object{
	t_type type;
	void *object_ptr; //物体の実体へのポインタ
	struct s_object *next;
} t_object;

#endif
