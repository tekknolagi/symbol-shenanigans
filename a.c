#include <stdio.h>
#include "test.h"

void load_module_a() {
  printf("Hello from module A!\n");
  register_it('A');
}
