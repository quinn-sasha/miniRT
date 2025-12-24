#ifndef PARSE_UTILS_H
#define PARSE_UTILS_H

#include "material.h"
#include "vec3.h"

int parse_double(const char *str, double *result);
int parse_double_range(const char *str, double *result, double min, double max);
int parse_clamped_double(const char *str, double *result, double min,
                         double max);
int parse_color(const char *str, t_color *color);
int parse_vector(const char *str, t_vec3 *output);
int parse_unit_vector(const char *str, t_vec3 *output);
t_material parse_material(const char *type, t_color albedo);

#endif // !PARSE_UTILS_H
