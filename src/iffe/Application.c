#include "Application.h"

struct Application
{
  vector(ref(Widget)) windows;
};

ref(Application) _ApplicationCreate()
{
  ref(Application) rtn = allocate(Application);
  _(rtn).windows = vector_new(ref(Widget));

  ApplicationAdd(rtn, MainWindow);

  return rtn;
}

void _ApplicationDestroy(ref(Application) ctx)
{
  foreach(ref(Widget) w, _(ctx).windows,
    _WidgetDestroy(w);
  )

  vector_delete(_(ctx).windows);
  release(ctx);
}

void _ApplicationRun(ref(Application) ctx)
{

}

ref(Widget) _ApplicationAdd(ref(Application) ctx, const char *name)
{
  ref(Widget) rtn = _WidgetCreateRoot(ctx, name);
  vector_push(_(ctx).windows, rtn);

  return rtn;
}

