#ifndef ERROR_UTILS_H
#define ERROR_UTILS_H

#include "minirt.h"

#define MLX_ERROR "Minilibx library failed"

void print_error(const char *message);
int error_return(const char *message, int status);
void error_exit(const char *message);
void handle_mlx_error(t_program *data);
int handle_parse_error(char **strings);

#endif // !ERROR_UTILS_H
