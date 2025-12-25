#include "xmalloc.h"
#include "error_utils.h"
#include <stdlib.h>

void *xmalloc(size_t size) {
  void *result;

  result = malloc(size);
  if (result == NULL) {
    error_exit("xmalloc()");
  }
  return (result);
}
