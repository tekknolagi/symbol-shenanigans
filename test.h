#pragma once
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>

// On Windows we don't have weak symbols across executable/DLL boundary,
// so we look up register_it_impl in the main module at call time via
// GetProcAddress. GetModuleHandle(NULL) always returns the main exe.
static void register_it(int num) {
  typedef void (*register_it_fn)(int);
  register_it_fn fn = (register_it_fn)GetProcAddress(
      GetModuleHandleA(NULL), "register_it_impl");
  if (fn) fn(num);
  else printf("register_it fallback: %d\n", num);
}

#else

// Weak reference resolved by the dynamic linker at load time against
// the main executable. If the main module doesn't define register_it,
// the symbol stays null and we use the fallback.
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

#endif
