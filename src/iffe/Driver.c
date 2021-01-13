#include "Driver.h"

#include <dlfcn.h>

struct Driver
{
  void *handle;
  void *(*initialize)(int, char **);
  void (*cleanup)(void *);
  void *(*create_window)(void *);
};

#define SYM(N) \
  _(rtn).N = dlsym(_(rtn).handle, #N); \
  if(!_(rtn).N) \
  { \
    panic("Failed to access library function"); \
  }

ref(Driver) DriverCreate()
{
  ref(Driver) rtn = allocate(Driver);

  _(rtn).handle = dlopen("./libxaw.so", RTLD_NOW);

  if(!_(rtn).handle)
  {
    panic("Failed to load driver");
  }

  SYM(initialize)
  SYM(cleanup)
  SYM(create_window)

  return rtn;
}

void DriverDestroy(ref(Driver) ctx)
{
  // TODO
  release(ctx);
}

void *DriverInitialize(ref(Driver) ctx, int argc, char *argv[])
{
  return _(ctx).initialize(argc, argv);
}

void *DriverCreateWindow(ref(Driver) ctx, void *state)
{
  return _(ctx).create_window(state);
}
