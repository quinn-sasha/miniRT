/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_number_generator.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:25:17 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 14:25:18 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_NUMBER_GENERATOR_H
# define RANDOM_NUMBER_GENERATOR_H

# include <stdint.h>

# define SEED_VALUE64 0x9E3779B97F4A7C15ULL

typedef struct s_xorshift64_state
{
	uint64_t		data;
}					t_xorshift64_state;

t_xorshift64_state	init_xorshift64_state(void);
double				random_double(t_xorshift64_state *state);
double				random_double_range(t_xorshift64_state *state, double min,
						double max);

#endif // !RANDOM_NUMBER_GENERATOR_H
