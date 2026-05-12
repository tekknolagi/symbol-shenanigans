// for dlopen
#include <stdio.h>
#include <dlfcn.h>

void register_it_impl(int num) {
  printf("Registered number: %d\n", num);
}

int main() {
  void *handle_a = dlopen("./a.so", RTLD_LAZY);
  if (!handle_a) {
    fprintf(stderr, "Error loading a.so: %s\n", dlerror());
    return 1;
  }
  void (*load_module_a)() = dlsym(handle_a, "load_module_a");
  if (!load_module_a) {
    fprintf(stderr, "Error finding load_module_a: %s\n", dlerror());
    dlclose(handle_a);
    return 1;
  }
  load_module_a();
  // now b
  void *handle_b = dlopen("./b.so", RTLD_LAZY);
  if (!handle_b) {
    fprintf(stderr, "Error loading b.so: %s\n", dlerror());
    dlclose(handle_a);
    return 1;
  }
  void (*load_module_b)() = dlsym(handle_b, "load_module_b");
  if (!load_module_b) {
    fprintf(stderr, "Error finding load_module_b: %s\n", dlerror());
    dlclose(handle_a);
    dlclose(handle_b);
    return 1;
  }
  load_module_b();
}
