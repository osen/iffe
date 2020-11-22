#include "Application.h"

struct Application
{
  int dummy;
};

ref(Application) _ApplicationCreate()
{
  ref(Application) rtn = allocate(Application);

  return rtn;
}

void _ApplicationDestroy(ref(Application) ctx)
{
  release(ctx);
}

void _ApplicationRun(ref(Application) ctx)
{

}

