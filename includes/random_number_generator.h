#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

#include <stdint.h>

#define SEED_VALUE64 0x9E3779B97F4A7C15ULL //黄金比の逆数　ビットが均等に分散する特性がある
#define INVERSE_TWO_POW_53 (1.0 / 9007199254740992.0)

//乱数生成器が次にどのような乱数を生成すべきかを記憶しておくための状態(state)
typedef struct s_xorshift64_state {
  uint64_t data;
} t_xorshift64_state;

void init_xorshift64_state(t_xorshift64_state *state);
double random_double(t_xorshift64_state *state);
double random_double_range(t_xorshift64_state *state, double min, double max);

#endif
