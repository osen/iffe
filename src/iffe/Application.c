#include "Application.h"
#include "Widget.h"

struct Application
{
  vector(ref(Widget)) windows;
#ifdef USE_X11
  Display *display;
  int screen;
#endif
};

ref(Application) _application;

ref(Application) _ApplicationCreate()
{
  ref(Application) rtn = allocate(Application);
  _application = rtn;
  _(rtn).windows = vector_new(ref(Widget));

#ifdef USE_X11
  _(rtn).display = XOpenDisplay(NULL);

  if(!_(rtn).display)
  {
    panic("Failed to open display");
  }

  _(rtn).screen = DefaultScreen(_(rtn).display);
#endif

  WidgetAdd(NULL, MainWindow);

  return rtn;
}

void _ApplicationDestroy(ref(Application) ctx)
{
  foreach(ref(Widget) w, _(ctx).windows,
    _WidgetDestroy(w);
  )

  vector_delete(_(ctx).windows);

#ifdef USE_X11
  XCloseDisplay(_(ctx).display);
#endif

  release(ctx);
}

void _ApplicationRun(ref(Application) ctx)
{
#ifdef USE_X11
  XEvent e = {0};

  while(vector_size(_(ctx).windows) > 0)
  {
    ref(Widget) w = NULL;

    XNextEvent(_(ctx).display, &e);

    foreach(w, _(ctx).windows,
      if(_WidgetWindow(w) == e.xany.window) break;
      w = NULL;
    )

    if(!w) continue;
  }
#endif
}

void _ApplicationAddWidget(ref(Application) ctx, ref(Widget) widget)
{
  vector_push(_(ctx).windows, widget);
}

#ifdef USE_X11
Display *_ApplicationDisplay(ref(Application) ctx)
{
  return _(ctx).display;
}

int _ApplicationScreen(ref(Application) ctx)
{
  return _(ctx).screen;
}
#endif
