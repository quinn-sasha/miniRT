#include "random_number_generator.h"
#include <iso646.h>

uint64_t xorshift64(t_xorshift64_state *state) {
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
