/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:49:20 by squinn            #+#    #+#             */
/*   Updated: 2025/12/25 18:50:01 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_atof.h"
#include "parse.h"
#include "parse_utils.h"
#include "utilities.h"

// Return PARSE_SUCCESS if success, otherwise PARSE_FAILED
int	parse_double(const char *str, double *result)
{
	if (!is_floating_point(str))
		return (PARSE_FAILED);
	*result = ft_atof(str);
	return (PARSE_SUCCESS);
}

// Return PARSE_SUCCESS if success, otherwise PARSE_FAILED
int	parse_double_range(const char *str, double *result, double min, double max)
{
	if (parse_double(str, result) == PARSE_FAILED)
		return (PARSE_FAILED);
	if (*result < min || *result > max)
		return (PARSE_FAILED);
	return (PARSE_SUCCESS);
}

// Return PARSE_SUCCESS if success, otherwise PARSE_FAILED
int	parse_clamped_double(const char *str, double *result, double min,
		double max)
{
	if (parse_double(str, result) == PARSE_FAILED)
		return (PARSE_FAILED);
	if (*result < min)
		*result = min;
	else if (*result > max)
		*result = max;
	return (PARSE_SUCCESS);
}
