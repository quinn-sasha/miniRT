/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:27:01 by ikota             #+#    #+#             */
/*   Updated: 2025/12/27 14:27:02 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

typedef struct s_img
{
	void	*mlx_img;
	char	*address;
	int		bits_per_pixel;
	int		row_size;
	int		endian;
}			t_img;

#endif // !IMG_H
