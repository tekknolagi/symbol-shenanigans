#include <stdio.h>
#include "test.h"

void load_module_b() {
  printf("Hello from module B!\n");
  register_it('B');
}
