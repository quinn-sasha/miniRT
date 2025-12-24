#ifndef PARSE_UTILS_H
#define PARSE_UTILS_H

#include "material.h"
#include "vec3.h"

int parse_floating_point(const char *str, double *result);
int parse_color(const char *str, t_color *color);
int parse_vector(const char *str, t_vec3 *output);
t_material parse_material(const char *type, t_color albedo);

#endif // !PARSE_UTILS_H
