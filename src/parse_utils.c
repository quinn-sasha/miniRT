#include "parse_utils.h"
#include "color.h"
#include "ft_atof.h"
#include "libft.h"
#include "material.h"
#include "parse.h"
#include "utilities.h"
#include "vec3.h"

// Return PARSE_SUCCESS if success, otherwise PARSE_FAILED
int parse_double(const char *str, double *result) {
  if (!is_floating_point(str))
    return PARSE_FAILED;
  *result = ft_atof(str);
  return PARSE_SUCCESS;
}

int parse_double_range(const char *str, double *result, double min,
                       double max) {
  if (parse_double(str, result) == PARSE_FAILED)
    return PARSE_FAILED;
  if (*result < min || *result > max)
    return PARSE_FAILED;
  return PARSE_SUCCESS;
}

int parse_clamped_double(const char *str, double *result, double min,
                         double max) {
  if (parse_double(str, result) == PARSE_FAILED)
    return PARSE_FAILED;
  if (*result < min)
    *result = min;
  else if (*result > max)
    *result = max;
  return PARSE_SUCCESS;
}

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
int parse_color(const char *str, t_color *color) {
  char **colors = ft_split(str, ',');
  if (count_strings(colors) != 3) {
    free_strings(colors);
    return PARSE_FAILED;
  }
  int i = 0;
  while (colors[i]) {
    if (!is_unsigned_int(colors[i])) {
      free_strings(colors);
      return PARSE_FAILED;
    }
    i++;
  }
  double r = (double)ft_atoi(colors[0]) / 255;
  double g = (double)ft_atoi(colors[1]) / 255;
  double b = (double)ft_atoi(colors[2]) / 255;
  *color = init_color(r, g, b);
  free_strings(colors);
  return PARSE_SUCCESS;
}

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
int parse_vector(const char *str, t_vec3 *output) {
  char **coordinates = ft_split(str, ',');
  if (count_strings(coordinates) != 3) {
    free_strings(coordinates);
    return PARSE_FAILED;
  }
  int i = 0;
  while (coordinates[i]) {
    if (!is_floating_point(coordinates[i])) {
      free_strings(coordinates);
      return PARSE_FAILED;
    }
    i++;
  }
  output->x = ft_atof(coordinates[0]);
  output->y = ft_atof(coordinates[1]);
  output->z = ft_atof(coordinates[2]);
  free_strings(coordinates);
  return PARSE_SUCCESS;
}

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
int parse_unit_vector(const char *str, t_vec3 *output) {
  if (parse_vector(str, output) == PARSE_FAILED)
    return PARSE_FAILED;
  if (length_squared_vec3(*output) != 1.0)
    return PARSE_FAILED;
  return PARSE_SUCCESS;
}

// typeが不明な場合もlambertianを返す
t_material parse_material(const char *type, t_color albedo) {
  if (ft_strcmp(type, "metal") == 0) {
    return init_metal_material(albedo, 0);
  }
  if (ft_strcmp(type, "dielectric") == 0) {
    return init_dielectric_material(1.5); // TODO: only accepts glass
  }
  return init_lambertian_material(albedo);
}
