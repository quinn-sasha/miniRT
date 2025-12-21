#include "random_number_generator.h"
#include <iso646.h>

void init_xorshift64_state(t_xorshift64_state *state) {
  state->data = SEED_VALUE64;
}

static uint64_t xorshift64(t_xorshift64_state *state) {
  uint64_t x = state->data;
  x ^= x << 3;
  x ^= x >> 35;
  x ^= x << 14;
  state->data = x;
  return x;
}

double random_double(t_xorshift64_state *state) {
  uint64_t result = xorshift64(state);
  return (result >> 11) * INVERSE_TWO_POW_53;
}

double random_double_range(t_xorshift64_state *state, double min, double max) {
  return min + (max - min) * random_double(state);
}
