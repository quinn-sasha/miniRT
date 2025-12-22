#include "camera.h"
#include "color.h"
#include "error_utils.h"
#include "hit_record.h"
#include "material.h"
#include "minilibx_utils.h"
#include "mlx.h"
#include "object_list.h"
#include "random_number_generator.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"
#include "light.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ccalulate runtime
#include <time.h>

static void generate_random_scene(t_scene_object *head,
                                  t_xorshift64_state *state) {
  t_material ground_material =
      init_lambertian_material(init_color(0.5, 0.5, 0.5));
  add_sphere(head, new_sphere(init_vec3(0, -1000, 0), 1000, ground_material));

  for (int i = -11; i < 11; i++) {
    for (int j = -11; j < 11; j++) {
      t_vec3 center = init_vec3(i + 0.9 * random_double(state), 0.2,
                                j + 0.9 * random_double(state));
      if (length_vec3(sub_vec3(center, init_vec3(4, 0.2, 0))) <= 0.9)
        continue;
      double material_decision = random_double(state);
      t_material sphere_material;
      if (material_decision < 0.8) {
        t_color albedo =
            multiply_vec3(init_random_vec3(state), init_random_vec3(state));
        sphere_material = init_lambertian_material(albedo);
        add_sphere(head, new_sphere(center, 0.2, sphere_material));
        continue;
      }
      if (material_decision < 0.95) {
        t_color albedo = init_random_vec3_range(state, 0.5, 1);
        double fuzziness = random_double_range(state, 0, 0.5);
        sphere_material = init_metal_material(albedo, fuzziness);
        add_sphere(head, new_sphere(center, 0.2, sphere_material));
        continue;
      }
      sphere_material = init_dielectric_material(1.5); // glass: 1.5
      add_sphere(head, new_sphere(center, 0.2, sphere_material));
    }
  }
  t_material material1 = init_dielectric_material(1.5);
  add_sphere(head, new_sphere(init_vec3(0, 1, 0), 1.0, material1));
  t_material material2 = init_lambertian_material(init_color(0.4, 0.2, 0.1));
  add_sphere(head, new_sphere(init_vec3(-4, 1, 0), 1.0, material2));
  t_material material3 = init_metal_material(init_color(0.7, 0.6, 0.5), 0.0);
  add_sphere(head, new_sphere(init_vec3(4, 1, 0), 1.0, material3));
}

static t_color calculate_direct_lighting(t_hit_record *record, t_scene_object *head,
                                         t_light *light){

  t_vec3 light_dir_vec = sub_vec3(light->pos, record->intersection);
  double distance_to_light = length_vec3(light_dir_vec);
  t_vec3 normalized_light_dir_vec = normalize_vec3(light_dir_vec);

  t_ray shadow_ray;

  t_ray shadow_ray = init_ray(record->intersection, normalized_light_dir_vec); 
 
  t_hit_record shadow_rec;

  if (hits_any_object(head, shadow_ray, 0.001, distance_to_light, &shadow_rec))
      return init_color(0, 0, 0); //影生成

  //TODO: calculate_diffuse()関数をつくる。拡散反射の計算   
  double dot_nl = dot_vec3(record->normal_vector, normalized_light_dir_vec);
  if (dot_nl < 0) dot_nl = 0; //この条件に入るときは光が裏側から入るので０にする
  //反射光 = 光源の色 * 輝度比 * cosθ
  t_color diffuse = scale_vec3(light->color, light->brightness_ratio * dot_nl);）
  t_color specular = init_color(0, 0, 0);

  if (record->material.type == MAT_METAL)
  {
    // TODO: calculate_specular() 金属の場合は鏡面反射（ハイライト）も計算する
    specular = calculate_specular(record, light, ray_in);
  }
  // 最終的に足して返す
  return add_vec3(diffuse, specular);
  return multiply_vec3(record->material.albedo, diffuse);
}

static t_color calculate_color(t_ray ray, t_program *data,
                               t_xorshift64_state *state, int num_recursions) {
  if (num_recursions <= 0)
    return init_color(0, 0, 0);
  t_hit_record record;

  if (hits_any_object(&data->head, ray, 0.001, INFINITY, &record)){
    t_color direct_light = init_color(0, 0, 0);
    t_color indirect_light = init_color(0, 0, 0);
    t_color attenuation = record.material.albedo;
    t_ray scattered;

    //直接光の計算
  if (record.material.type == MAT_LAMBERTIAN || record.material.type == MAT_METAL){
    //TODO: ここでscene内の全高原をループする処理を呼ぶ
    direct_light = calculate_direct_lighting(&record, &data->head, &data->light);
    //内部で影ができるかのチェックとDiffuse / Specular計算を行う。
  }
   //間接光の計算
    bool can_scatter = false;
    if (record.material.type == MAT_LAMBERTIAN)
      can_scatter = lambertian_scatters(record, &scattered, state);
    else if (record.material.type == MAT_METAL)
      can_scatter = metal_scatters(ray, record, &scattered, state);
    else if (record.material.type == MAT_DIELECTRIC)
      can_scatter = dielectric_scatters(ray, record, &scattered, &attenuation, state);
    if (can_scatter){
      t_color recursive_color = calculate_color(scattered, data, state, num_recursions - 1);
      indirect_light = multiply_vec3(recursive_color, attenuation);
    }
    //環境光を考慮する
    t_color ambient_effect = scale_vec3(data->ambient.color, data->ambient.ratio);
    t_color final_ambient = multiply_vec3(record.material.albedo, ambient_effect);
    return (clamp_color(add_triple_vec3(direct_light, indirect_light, final_ambient)));
  }
  t_vec3 normalized_direction = normalize_vec3(ray.direction);
  double t = 0.5 * (normalized_direction.y + 1.0);
  t_color white = init_color(1.0, 1.0, 1.0);
  return add_vec3(scale_vec3(white, (1.0 - t)),
                  scale_vec3(init_color(0.5, 0.7, 1.0), t));
}

static void set_up_camera(t_program *data) {
  t_vec3 lookfrom = init_vec3(13, 2, 3);
  t_vec3 lookat = init_vec3(0, 0, 0);
  t_vec3 view_up = init_vec3(0, 1, 0);
  double focus_dist = 10.0;
  t_camera camera = init_camera(lookfrom, lookat, view_up,
                                (double)WIDTH / HEIGHT, 20, 0.1, focus_dist);
  data->camera = camera;
}

int render(t_program *data) {
  if (data->window == NULL)
    return (EXIT_SUCCESS);

  t_xorshift64_state state;
  init_xorshift64_state(&state);
  generate_random_scene(&data->head, &state);

  init_light(&data->light);
  init_ambient(&data->ambient);

  printf("Rendering started\n");
  clock_t begin = clock();
  const int max_recursions = 50;
  const int num_samples_per_pixel = 100;
  for (int y = 0; y < HEIGHT; y++) {
    printf("Scanlines reamaining: %d\n", HEIGHT - y);
    for (int x = 0; x < WIDTH; x++) {

      t_color pixel_color = init_color(0, 0, 0);
      for (int sample = 0; sample < num_samples_per_pixel; sample++) {
        double x_offset = (x + random_double(&state)) / (WIDTH - 1);
        double y_offset = (y + random_double(&state)) / (HEIGHT - 1);
        t_ray ray = get_ray(data->camera, x_offset, y_offset, &state);
        pixel_color =
            add_vec3(pixel_color,
                     calculate_color(ray, data, &state, max_recursions));
      }
      pixel_color = divide_vec3(pixel_color, num_samples_per_pixel);
      gamma_correction(&pixel_color);
      set_pixel_color(x, y, &data->img, rgb_to_integer(pixel_color));
    }
  }
  mlx_put_image_to_window(data->mlx, data->window, data->img.mlx_img, 0, 0);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time spent: %lf seconds\n", time_spent);
  printf("Rendering done\n");
  return EXIT_SUCCESS;
}

int main(void) {
  // TODO: read from rt file
  t_program data;
  init_mlx_resources(&data);
  set_mlx_hooks(&data);
  init_dummy_head(&data.head); // TODO
  set_up_camera(&data);
  render(&data);
  mlx_loop(data.mlx);
  destroy_mlx_resources_if_allocated(&data);
  destroy_object_list(&data.head);
  return EXIT_SUCCESS;
}
