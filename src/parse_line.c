#include "parse_line.h"
#include "camera.h"
#include "cylinder.h"
#include "error_utils.h"
#include "libft.h"
#include "material.h"
#include "minirt.h"
#include "object_list.h"
#include "parse.h"
#include "parse_utils.h"
#include "utilities.h"
#include "vec3.h"
#include <math.h>

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
int parse_ambient_helper(const char *line, t_elements_count *counts,
                         t_program *data) {
  counts->num_ambient++;
  char **params = ft_split(line, ' ');
  if (count_strings(params) != 3)
    return handle_parse_error(params);
  double brightness;
  if (parse_clamped_double(params[1], &brightness, 0.0, 1.0) == PARSE_FAILED)
    return handle_parse_error(params);
  t_color albedo;
  if (parse_color(params[2], &albedo) == PARSE_FAILED)
    return handle_parse_error(params);
  data->ambient = init_ambient(brightness, albedo);
  free_strings(params);
  return PARSE_SUCCESS;
}

int parse_ambient(const char *line, t_elements_count *counts, t_program *data) {
  int result = parse_ambient_helper(line, counts, data);
  if (result == PARSE_FAILED)
    return error_return("Invalid ambient setting", PARSE_FAILED);
  return PARSE_SUCCESS;
}

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
int parse_camera_helper(const char *line, t_elements_count *counts,
                        t_program *data) {
  counts->num_cameras++;
  char **params = ft_split(line, ' ');
  if (count_strings(params) != 4)
    return handle_parse_error(params);
  t_vec3 lookfrom;
  if (parse_vector(params[1], &lookfrom) == PARSE_FAILED)
    return handle_parse_error(params);
  t_vec3 direction;
  if (parse_unit_vector(params[2], &direction) == PARSE_FAILED)
    return handle_parse_error(params);
  double hfov;
  if (parse_double_range(params[3], &hfov, 0, 180) == PARSE_FAILED)
    return handle_parse_error(params);
  setup_camera(lookfrom, direction, hfov, data);
  free_strings(params);
  return PARSE_SUCCESS;
}

int parse_camera(const char *line, t_elements_count *counts, t_program *data) {
  if (parse_camera_helper(line, counts, data) == PARSE_FAILED)
    return error_return("Invalid camera setting", PARSE_FAILED);
  return PARSE_SUCCESS;
}

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
int parse_light_helper(const char *line, t_elements_count *counts,
                       t_program *data) {
  counts->num_lights++;
  char **params = ft_split(line, ' ');
  if (count_strings(params) != 4)
    return handle_parse_error(params);
  t_vec3 pos;
  if (parse_vector(params[1], &pos) == PARSE_FAILED)
    return handle_parse_error(params);
  double brightness;
  if (parse_clamped_double(params[2], &brightness, 0.0, 1.0) == PARSE_FAILED)
    return handle_parse_error(params);
  t_color color;
  if (parse_color(params[3], &color) == PARSE_FAILED)
    return handle_parse_error(params);
  data->light = init_light(pos, brightness, color);
  free_strings(params);
  return PARSE_SUCCESS;
}

int parse_light(const char *line, t_elements_count *counts, t_program *data) {
  if (parse_light_helper(line, counts, data) == PARSE_FAILED)
    return error_return("Invalid light setting", PARSE_FAILED);
  return PARSE_SUCCESS;
}

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
// TODO: rt file をカスタマイズした部分を説明する
int parse_sphere_helper(const char *line, t_program *data) {
  char **params = ft_split(line, ' ');
  if (count_strings(params) != 5)
    return handle_parse_error(params);
  t_vec3 center;
  if (parse_vector(params[1], &center) == PARSE_FAILED)
    return handle_parse_error(params);
  double diameter;
  if (parse_double_range(params[2], &diameter, 0, INFINITY) == PARSE_FAILED)
    return handle_parse_error(params);
  t_color albedo;
  if (parse_color(params[3], &albedo) == PARSE_FAILED)
    return handle_parse_error(params);
  t_material material = parse_material(params[4], albedo);
  add_sphere(&data->head, new_sphere(center, diameter / 2, material));
  free_strings(params);
  return PARSE_SUCCESS;
}

int parse_sphere(const char *line, t_program *data) {
  if (parse_sphere_helper(line, data) == PARSE_FAILED)
    return error_return("Invalid sphere setting", PARSE_FAILED);
  return PARSE_SUCCESS;
}

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
int parse_plane_helper(const char *line, t_program *data) {
  char **params = ft_split(line, ' ');
  if (count_strings(params) != 5)
    return handle_parse_error(params);
  t_vec3 point;
  if (parse_vector(params[1], &point) == PARSE_FAILED)
    return handle_parse_error(params);
  t_vec3 normal;
  if (parse_unit_vector(params[2], &normal) == PARSE_FAILED)
    return handle_parse_error(params);
  t_color albedo;
  if (parse_color(params[3], &albedo) == PARSE_FAILED)
    return handle_parse_error(params);
  t_material material = parse_material(params[4], albedo);
  add_plane(&data->head, new_plane(point, normal, material));
  free_strings(params);
  return PARSE_SUCCESS;
}

int parse_plane(const char *line, t_program *data) {
  if (parse_plane_helper(line, data) == PARSE_FAILED)
    return error_return("Invalid plane setting", PARSE_FAILED);
  return PARSE_SUCCESS;
}

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
// TODO: 長さ = 0などの無効な入力を弾いていない
int parse_cylinder_helper(const char *line, t_program *data) {
  char **params = ft_split(line, ' ');
  if (count_strings(params) != 7)
    return handle_parse_error(params);
  t_vec3 center;
  if (parse_vector(params[1], &center) == PARSE_FAILED)
    return handle_parse_error(params);
  t_vec3 axis;
  if (parse_unit_vector(params[2], &axis) == PARSE_FAILED)
    return handle_parse_error(params);
  double diameter;
  if (parse_double_range(params[3], &diameter, 0, INFINITY) == PARSE_FAILED)
    return handle_parse_error(params);
  double height;
  if (parse_double_range(params[4], &height, 0, INFINITY) == PARSE_FAILED)
    return handle_parse_error(params);
  t_color albedo;
  if (parse_color(params[5], &albedo) == PARSE_FAILED)
    return handle_parse_error(params);
  t_material material = parse_material(params[6], albedo);
  add_cylinder(&data->head,
               new_cylinder(center, axis, diameter / 2, height, material));
  free_strings(params);
  return PARSE_SUCCESS;
}

int parse_cylinder(const char *line, t_program *data) {
  if (parse_cylinder_helper(line, data) == PARSE_FAILED)
    return error_return("Invalid cylinder setting", PARSE_FAILED);
  return PARSE_SUCCESS;
}

// Return PARSE_SUCCESS if succeed, otherwise PARSE_FAILED
int parse_line(const char *line, t_elements_count *counts, t_program *data) {
  if (ft_strncmp(line, "A", 1) == 0)
    return parse_ambient(line, counts, data);
  if (ft_strncmp(line, "C", 1) == 0)
    return parse_camera(line, counts, data);
  if (ft_strncmp(line, "L", 1) == 0)
    return parse_light(line, counts, data);
  if (ft_strncmp(line, "sp", 2) == 0)
    return parse_sphere(line, data);
  if (ft_strncmp(line, "pl", 2) == 0)
    return parse_plane(line, data);
  if (ft_strncmp(line, "cy", 2) == 0)
    return parse_cylinder(line, data);
  return error_return("Unknown identifier", PARSE_FAILED);
}
