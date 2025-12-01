#include <stdio.h>
#include <unistd.h>

int main(void) {
  const int image_height = 256;
  const int image_width = 256;

  printf("P3\n");
  printf("%d %d\n255\n", image_width, image_height);

  for (int col = image_height - 1; col >= 0; col--) {
    for (int row = 0; row < image_width; row++) {
      dprintf(STDERR_FILENO, "Scanlines remaining: %d ", col);
      double r = (double)row / (image_width - 1);
      double g = (double)col / (image_height - 1);
      double b = 0.25;

      int ir = (int)(255.999 * r);
      int ig = (int)(255.999 * g);
      int ib = (int)(255.999 * b);

      printf("%d %d %d\n", ir, ig, ib);
    }
    dprintf(STDERR_FILENO, "Done\n");
  }
}
