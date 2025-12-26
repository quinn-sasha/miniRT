/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:54:01 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 14:54:02 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include <stdbool.h>
# include <stddef.h>

// string_utils.c
size_t	count_strings(char **strings);
void	free_strings(char **strings);
// utilities1.c
double	clamp(double x, double lower_limit, double upper_limit);
double	min_double(double a, double b);
double	ft_fabs(double x);
// utilities2.c
bool	is_unsigned_int(char *str);
bool	is_floating_point(const char *str);
int		ft_isspace(int c);

#endif // !UTILITIES_H
