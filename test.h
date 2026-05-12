#pragma once
#include <stdio.h>

// Weak reference resolved by the dynamic linker at load time against
// the main executable. If the main module doesn't define register_it,
// the symbol stays null and callers should use register_it_fallback.
#if __has_attribute(weak_import)
extern void register_it_impl(int num) __attribute__((weak_import));
#else
extern void register_it_impl(int num) __attribute__((weak));
#endif

static void register_it(int num) {
  if (&register_it_impl) {
    register_it_impl(num);
  } else {
    printf("register_it fallback: %d\n", num);
  }
}
