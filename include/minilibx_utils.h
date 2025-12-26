/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:27:38 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 18:27:39 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBX_UTILS_H
# define MINILIBX_UTILS_H

# define KEYPRESSMASK 1
# define KEYPRESS 2
# define DESTROYNOTIFY 17
# ifdef __linux__
#  define XK_ESCAPE 0xff1b
# else
#  define XK_ESCAPE 53
# endif

# include "img.h"
# include "minirt.h"
# include <stdint.h>

void	set_pixel_color(int x, int y, t_img *img, uint32_t color);
void	init_mlx_resources(t_program *data);
void	destroy_mlx_resources_if_allocated(t_program *data);
void	set_mlx_hooks(t_program *data);

#endif // !MINILIBX_UTILS_H
