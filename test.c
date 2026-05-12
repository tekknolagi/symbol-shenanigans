#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
typedef HMODULE lib_handle_t;
#define lib_open(name) LoadLibraryA(name)
#define lib_sym(h, name) (void *)GetProcAddress((h), (name))
#define lib_close(h) FreeLibrary(h)
#define LIB_EXT ".dll"
#define LIB_EXPORT __declspec(dllexport)
#else
#include <dlfcn.h>
typedef void *lib_handle_t;
#define lib_open(name) dlopen((name), RTLD_LAZY)
#define lib_sym(h, name) dlsym((h), (name))
#define lib_close(h) dlclose(h)
#define LIB_EXT ".so"
#define LIB_EXPORT
#endif

#ifdef DEFINE_REGISTER_IT
LIB_EXPORT void register_it_impl(int num) {
  printf("Registered number: %d\n", num);
}
#endif

int main() {
  lib_handle_t handle_a = lib_open("./a" LIB_EXT);
  if (!handle_a) {
    fprintf(stderr, "Error loading a%s\n", LIB_EXT);
    return 1;
  }
  void (*load_module_a)() = (void (*)())lib_sym(handle_a, "load_module_a");
  if (!load_module_a) {
    fprintf(stderr, "Error finding load_module_a\n");
    lib_close(handle_a);
    return 1;
  }
  load_module_a();
  // now b
  lib_handle_t handle_b = lib_open("./b" LIB_EXT);
  if (!handle_b) {
    fprintf(stderr, "Error loading b%s\n", LIB_EXT);
    lib_close(handle_a);
    return 1;
  }
  void (*load_module_b)() = (void (*)())lib_sym(handle_b, "load_module_b");
  if (!load_module_b) {
    fprintf(stderr, "Error finding load_module_b\n");
    lib_close(handle_a);
    lib_close(handle_b);
    return 1;
  }
  load_module_b();
}
