#pragma once

void register_it_hook(int num) __attribute__((weak));
// weak symbol in case register_it is not defined in the main program

void register_it(int num) {
  if (register_it_hook) {
    register_it_hook(num);
  } else {
    printf("WEAK\n");
  }
}
