#include "Driver.h"

#include <dlfcn.h>

struct Driver
{
  void *handle;
  void *state;
  void *(*initialize)(int, char **);
  void (*cleanup)(void *);
  void *(*create_window)(void *);
  void (*run)(void *);
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
  SYM(run)

  return rtn;
}

void DriverDestroy(ref(Driver) ctx)
{
  // TODO
  release(ctx);
}

void *DriverInitialize(ref(Driver) ctx, int argc, char *argv[])
{
  _(ctx).state = _(ctx).initialize(argc, argv);

  return _(ctx).state;
}

void *DriverCreateWindow(ref(Driver) ctx)
{
  return _(ctx).create_window(_(ctx).state);
}

void DriverRun(ref(Driver) ctx)
{
  _(ctx).run(_(ctx).state);
}

