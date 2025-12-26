/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 20:03:09 by squinn            #+#    #+#             */
/*   Updated: 2025/12/25 20:03:10 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minirt.h"

# define PARSE_FAILED -1
# define PARSE_SUCCESS 0

typedef struct s_elements_count
{
	int	num_ambient;
	int	num_cameras;
	int	num_lights;
}		t_elements_count;

void	parse(int argc, char *argv[], t_program *data);

#endif // !PARSE_H
