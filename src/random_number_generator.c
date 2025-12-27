/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_number_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:35:45 by squinn            #+#    #+#             */
/*   Updated: 2025/12/26 14:35:46 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "random_number_generator.h"
#include <iso646.h>

t_xorshift64_state	init_xorshift64_state(void)
{
	t_xorshift64_state	state;

	state.data = SEED_VALUE64;
	return (state);
}

static uint64_t	xorshift64(t_xorshift64_state *state)
{
	uint64_t	x;

	x = state->data;
	x ^= x << 3;
	x ^= x >> 35;
	x ^= x << 14;
	state->data = x;
	return (x);
}

double	random_double(t_xorshift64_state *state)
{
	static const double	inverse_two_pow_53 = 1.0 / 9007199254740992.0;
	uint64_t			result;

	result = xorshift64(state);
	return ((result >> 11) * inverse_two_pow_53);
}

double	random_double_range(t_xorshift64_state *state, double min, double max)
{
	return (min + (max - min) * random_double(state));
}
