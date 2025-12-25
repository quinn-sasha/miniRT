#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdbool.h>
#include <stddef.h>

double clamp(double x, double lower_limit, double upper_limit);
double min_double(double a, double b);
size_t count_strings(char **strings);
void free_strings(char **strings);
bool is_unsigned_int(char *str);
bool is_floating_point(const char *str);
double ft_fabs(double x);
int ft_isspace(int c);

#endif // !UTILITIES_H
