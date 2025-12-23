#include "error_utils.h"
#include "libft.h"
#include "minilibx_utils.h"
#include <stdlib.h>

void print_error(const char *message) { ft_printf("Error: %s\n", message); }

void error_exit(const char *message) {
  ft_printf("Error: %s\n", message);
  exit(EXIT_FAILURE);
}

void handle_mlx_error(t_program *data) {
  destroy_mlx_resources_if_allocated(data);
  error_exit(MLX_ERROR);
}
