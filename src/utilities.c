#include "utilities.h"
#include "libft.h"
#include <stdlib.h>

double clamp(double x, double lower_limit, double upper_limit) {
  if (x < lower_limit)
    return lower_limit;
  if (x > upper_limit)
    return upper_limit;
  return x;
}

double min_double(double a, double b) {
  if (a < b)
    return a;
  return b;
}

size_t count_strings(char **strings) {
  size_t i;

  i = 0;
  while (strings[i] != NULL)
    i++;
  return (i);
}

void free_strings(char **strings) {
  int i;

  if (strings == NULL)
    return;
  i = 0;
  while (strings[i]) {
    free(strings[i]);
    i++;
  }
  free(strings);
}

// オーバーフローなどのチェックはしていない
bool is_unsigned_int(char *str) {
  int i;

  i = 0;
  while (str[i]) {
    if (!ft_isdigit(str[i]))
      return false;
    i++;
  }
  return true;
}

// 10進数以外の数や、指数標記に対応してない
bool is_floating_point(const char *str) {
  int i = 0;
  if (str[i] == '-')
    i++;
  while (str[i]) {
    if (!ft_isdigit(str[i]) && str[i] != '.')
      return false;
    i++;
  }
  return true;
}
