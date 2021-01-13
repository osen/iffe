#include "Driver.h"

#include <dlfcn.h>

struct Driver
{
  void *handle;
  void (*initialize)(int, char **);
};

ref(Driver) DriverCreate(int argc, char *argv[])
{
  ref(Driver) rtn = allocate(Driver);

  _(rtn).handle = dlopen("./libxaw.so", RTLD_NOW);

  if(!_(rtn).handle)
  {
    panic("Failed to load driver");
  }

  _(rtn).initialize = dlsym(_(rtn).handle, "_initialize");

  if(!_(rtn).initialize)
  {
    panic("Failed to access library function");
  }

  _(rtn).initialize(argc, argv);

  return rtn;
}

void DriverDestroy(ref(Driver) ctx)
{
  release(ctx);
}
