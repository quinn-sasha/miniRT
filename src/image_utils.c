/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikota <ikota@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:22:40 by ikota             #+#    #+#             */
/*   Updated: 2025/12/26 15:26:56 by ikota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_utils.h"
#include "mlx.h"

void set_pixel_color(int x, int y, t_img *img, uint32_t color) {
  int bytes_per_pixel;
  int offset;
  char *pixel_addr;

  bytes_per_pixel = img->bits_per_pixel / 8;
  offset = img->row_size * y + x * bytes_per_pixel;
  pixel_addr = img->address + offset;
  *(uint32_t *)pixel_addr = color;
}
