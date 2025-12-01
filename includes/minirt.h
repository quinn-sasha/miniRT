/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:20:08 by ikota             #+#    #+#             */
/*   Updated: 2025/12/01 12:45:42 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_list	t_list;
typedef struct s_dlist	t_dlist;

/****************************************************************************
*								MACROS										*
****************************************************************************/

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 0
# define ERROR -1

/****************************************************************************
*								VECTOR TYPES									*
****************************************************************************/

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vector3;

/****************************************************************************
*								COLOR TYPES								*
****************************************************************************/

typedef struct s_fcolor //float color
{
	double	red;
	double	green;
	double	blue;
}	t_fcolor;

/****************************************************************************
*								WORLD TYPES								*
****************************************************************************/

// A structure that holds object information,
// light source information, and other data

typedef struct s_world
{
	void			*mlx;
	void			*win;
	int				screen_width;
	int				screen_height;
	t_dlist			*cameras; //camera's list  double linked list
	t_list			*objects; //object's list
	t_fcolor		ambient; //ambient's strength
	t_list			*lights; //light's list
}	t_world;

/****************************************************************************
*								LIST TYPES								*
****************************************************************************/



/****************************************************************************
*								FUNCTIONS									*
****************************************************************************/

/* --------------------------- VECTOR ------------------------------*/

//vecor_utils.c
t_vector3	vec3_init(double x, double y, double z);
t_vector3	vec3_add(t_vector3 v1, t_vector3 v2);
t_vector3	vec3_sub(t_vector3 v1, t_vector3 v2);
t_vector3	vec3_dot(t_vector3 v1, t_vector3 v2);
t_vector3	vec3_length(t_vector3 v);
t_vector3	vec3_normalize(t_vector3 v);

/* --------------------------- COLOR ------------------------------*/


/* --------------------------- WORLD ------------------------------*/


#endif
