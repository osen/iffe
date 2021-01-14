#include "Application.h"
#include "Widget.h"
#include "Size.h"
#include "Rect.h"
#include "Driver.h"

#ifdef USE_X11
  #include <X11/Intrinsic.h>
  #include <X11/StringDefs.h>
#endif

struct Application
{
  vector(ref(Widget)) windows;
#ifdef USE_X11
  Display *display;
  int screen;
  XtAppContext context;
  Widget toplevel;
#endif
  int mustResize;
  ref(Driver) driver;
};

static char *fallback_resources[] = {
  "*Label.Label: Hello, World",
  NULL
};

ref(Application) _application;

ref(Application) _ApplicationCreate(int argc, char *argv[])
{
  ref(Application) rtn = allocate(Application);
  _application = rtn;
  _(rtn).windows = vector_new(ref(Widget));
  _(rtn).mustResize = 1;

  _(rtn).driver = DriverCreate();
  DriverInitialize(_(rtn).driver, argc, argv);

#ifdef USE_X11
  Arg wargs[10] = {0};
  int n = 0;
  //XtSetArg(wargs[n], XtNwidth, 640); n++;
  //XtSetArg(wargs[n], XtNheight, 480); n++;
  _(rtn).toplevel = XtAppInitialize(&_(rtn).context, "Xtodo", NULL, 0,
    &argc, argv, fallback_resources, wargs, n);

  //XtRealizeWidget(_(rtn).toplevel);

  _(rtn).display = XtDisplay(_(rtn).toplevel);
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
  // TODO
  //XCloseDisplay(_(ctx).display);
#endif

  DriverDestroy(_(ctx).driver);

  release(ctx);
}

void _ApplicationRequestResize(ref(Application) ctx)
{
  _(ctx).mustResize = 1;

/*
  foreach(ref(Widget) w, _(ctx).windows,
    XClearArea(_(ctx).display, _WidgetWindow(w), 0, 0, 0, 0, True);
  )
*/
}

void _ApplicationRun(ref(Application) ctx)
{
  DriverRun(_(ctx).driver);

#ifdef _USE_X11
  XEvent e = {0};

  while(vector_size(_(ctx).windows) > 0)
  {
    ref(Widget) w = NULL;

    if(_(ctx).mustResize)
    {
      _(ctx).mustResize = 0;

      foreach(ref(Widget) winw, _(ctx).windows,
        _WidgetResize(winw, WidgetSize(winw));
      )
    }

    XtAppNextEvent(_(ctx).context, &e);

    foreach(w, _(ctx).windows,
      if(_WidgetWindow(w) == e.xany.window) break;
      w = NULL;
    )

    if(!w)
    {
      XtDispatchEvent(&e);
      continue;
    }

    if(e.type == ConfigureNotify)
    {
      struct Rect s = WidgetBounds(w);

      if(s.w != e.xconfigure.width ||
        s.h != e.xconfigure.height)
      {
        _WidgetResize(w, SizeWh(e.xconfigure.width, e.xconfigure.height));
        //_WidgetDraw(w, RectXywh(0, 0, s.w, s.h));
      }
    }
    else if(e.type == Expose)
    {
      _WidgetDraw(w, RectXywh(e.xexpose.x, e.xexpose.y,
        e.xexpose.width, e.xexpose.height));
    }
    else if(e.type == ButtonPress)
    {
/*
      mouseDown.x = e.xbutton.x;
      mouseDown.y = e.xbutton.y;
      _WindowMouseDown(w, mouseDown);
*/
    }
    else if(e.type == ButtonRelease)
    {
/*
      mouseUp.x = e.xbutton.x;
      mouseUp.y = e.xbutton.y;
      _WindowMouseUp(w, mouseUp);
*/
    }
    else if(e.type == ClientMessage)
    {
      if(e.xclient.data.l[0] == _WidgetDeleteMessage(w))
      {
        WidgetDestroy(w);
      }
    }

    {size_t i = 0; for(; i < vector_size(_(ctx).windows); i++)
    {
      w = vector_at(_(ctx).windows, i);

      if(_WidgetDestroyed(w))
      {
        _WidgetDestroy(w);
        vector_erase(_(ctx).windows, i, 1);
        i--;
      }
    }}

    XtDispatchEvent(&e);
  }
#endif
}

void _ApplicationAddWidget(ref(Application) ctx, ref(Widget) widget)
{
  vector_push(_(ctx).windows, widget);
}

ref(Driver) ApplicationDriver(ref(Application) ctx)
{
  return _(ctx).driver;
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

Widget _ApplicationToplevel(ref(Application) ctx)
{
  return _(ctx).toplevel;
}

XtAppContext _ApplicationContext(ref(Application) ctx)
{
  return _(ctx).context;
}

#endif
