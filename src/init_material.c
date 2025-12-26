/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 00:35:20 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 00:35:21 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "material.h"

static t_material	init_material(t_color albedo)
{
	t_material	material;

	ft_memset(&material, 0, sizeof(t_material));
	material.albedo = albedo;
	return (material);
}

t_material	init_lambertian_material(t_color albedo)
{
	t_material	material;

	material = init_material(albedo);
	material.type = MAT_LAMBERTIAN;
	return (material);
}

t_material	init_metal_material(t_color albedo, double fuzziness)
{
	t_material	material;

	material = init_material(albedo);
	material.type = MAT_METAL;
	material.data.fuzziness = fuzziness;
	return (material);
}

// Dielectric doesn't have albedo
t_material	init_dielectric_material(double refractive_index)
{
	t_material	material;

	ft_memset(&material, 0, sizeof(t_material));
	material.type = MAT_DIELECTRIC;
	material.data.refractive_index = refractive_index;
	return (material);
}
