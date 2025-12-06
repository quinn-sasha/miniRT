#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

#include <stdint.h>

#define SEED_VALUE64 0x9E3779B97F4A7C15ULL
#define INVERSE_TWO_POW_53 (1.0 / 9007199254740992.0)

typedef struct s_xorshift64_state {
  uint64_t data;
} t_xorshift64_state;

uint64_t xorshift64(t_xorshift64_state *state);

#endif // !RANDOM_NUMBER_GENERATOR_H
