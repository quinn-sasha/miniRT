#include "color.h"
#include <stdio.h>
#include <unistd.h>
#include <vec3.h>

int main(void) {
  const int image_height = 256;
  const int image_width = 256;

  int fd = STDOUT_FILENO;
  dprintf(fd, "P3\n");
  dprintf(fd, "%d %d\n255\n", image_width, image_height);

  for (int col = image_height - 1; col >= 0; col--) {
    for (int row = 0; row < image_width; row++) {
      dprintf(STDERR_FILENO, "Scanlines remaining: %d ", col);

      t_color pixel_color = init_color((double)row / (image_width - 1),
                                       (double)col / (image_height - 1), 0.25);
      write_color(fd, pixel_color);
    }
  }
  dprintf(STDERR_FILENO, "Done\n");
}
