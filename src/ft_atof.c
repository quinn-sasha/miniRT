#include "libft.h"

int ft_isspace(int c) {
  if (c == ' ')
    return (1);
  if (c == '\f')
    return (1);
  if (c == '\n')
    return (1);
  if (c == '\r')
    return (1);
  if (c == '\t')
    return (1);
  if (c == '\v')
    return (1);
  return (0);
}

/*
 * Differeces from original atof:
 * 10進数のみに対応
 * オーバーフローとアンダーフローに対応してない
 * 指数表記(e.g. 1.2e-5)に対応してない
 */
double ft_atof(const char *str) {
  int i = 0;
  while (str[i] && ft_isspace(str[i]))
    i++;
  double sign = 1;
  if (str[i] == '+' || str[i] == '-') {
    if (str[i] == '-')
      sign = -1;
    i++;
  }
  double result = 0.0;
  double divisor = 1.0;
  while (str[i] && ft_isdigit(str[i])) {
    result = result * 10.0 + (str[i] - '0');
    i++;
  }
  if (str[i] != '.')
    return sign * result;
  i++;
  while (str[i] && ft_isdigit(str[i])) {
    result = result * 10.0 + (str[i] - '0');
    divisor *= 10;
    i++;
  }
  return sign * result / divisor;
}

/*
#include <assert.h>

int main(void) {
  assert(atof("0.0") == ft_atof("0.0"));
  assert(atof("0.001") == ft_atof("0.001"));
  assert(atof("5.0") == ft_atof("5.0"));
  assert(atof("-1.2") == ft_atof("-1.2"));
  assert(atof("10.98") == ft_atof("10.98"));
  assert(atof("-100.3") == ft_atof("-100.3"));
  return 0;
}
*/
