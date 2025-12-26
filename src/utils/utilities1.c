/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:51:53 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 14:51:54 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include <stdlib.h>

double	clamp(double x, double lower_limit, double upper_limit)
{
	if (x < lower_limit)
		return (lower_limit);
	if (x > upper_limit)
		return (upper_limit);
	return (x);
}

double	min_double(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

// Simpler version of original fabs
double	ft_fabs(double x)
{
	if (x < 0.0)
		return (-x);
	return (x);
}
