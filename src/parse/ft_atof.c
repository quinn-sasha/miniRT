/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:52:32 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 18:56:29 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utilities.h"
#include <stdbool.h>

static double	get_sign_and_skip(const char *str, int *i)
{
	double	sign;

	sign = 1.0;
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1.0;
		(*i)++;
	}
	return (sign);
}

double	ft_atof(const char *str)
{
	int		i;
	double	sign;
	double	res;
	double	div;

	i = 0;
	sign = get_sign_and_skip(str, &i);
	res = 0.0;
	div = 1.0;
	while (str[i] && ft_isdigit(str[i]))
		res = res * 10.0 + (str[i++] - '0');
	if (str[i] == '.')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		res = res * 10.0 + (str[i++] - '0');
		div *= 10.0;
	}
	return (sign * res / div);
}

/*
#include <assert.h>

int	main(void) {
  assert(atof("0.0") == ft_atof("0.0"));
  assert(atof("0.001") == ft_atof("0.001"));
  assert(atof("5.0") == ft_atof("5.0"));
  assert(atof("-1.2") == ft_atof("-1.2"));
  assert(atof("10.98") == ft_atof("10.98"));
  assert(atof("-100.3") == ft_atof("-100.3"));
  return (0);
}
*/
