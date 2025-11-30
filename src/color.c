#include "minirt.h"

uint32_t create_rgb(int red, int green, int blue) {
  uint32_t result = 0;
  result = result | blue;
  result = result | (green << 8);
  result = result | (red << 16);
  return result;
}
