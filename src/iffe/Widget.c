#include "Widget.h"
#include "events.h"
#include "Application.h"
#include "Size.h"
#include "Rect.h"
#include "Graphics.h"
#include "Color.h"
#include "FlowProcessor.h"
#include "Driver.h"

#ifdef USE_X11
  #include <X11/Intrinsic.h>
  #include <X11/IntrinsicP.h>
  #include <X11/Shell.h>
  #include <X11/StringDefs.h>
#endif

struct Widget
{
  ref(Application) application;
  ref(Widget) parent;
  vector(ref(Widget)) children;
  struct EventTable events;
  refvoid userData;
  ref(sstream) type;
  struct Size size;
  struct Rect bounds;
  ref(Graphics) graphics;
  ref(FlowProcessor) flowProcessor;
  struct Color background;
  int border;

  int destroyed;
  int drawn;

  void *_internal;

#ifdef USE_X11
  Window window;
  Atom deleteMessage;
  GC gc;
  Widget internal;
  Widget win;
#endif
};

ref(Widget)_widgetLastWidget;
extern ref(Application) _application;

static void _WidgetCreateWindow(ref(Widget) ctx)
{
  _(ctx)._internal = DriverCreateWindow(ApplicationDriver(WidgetApplication(ctx)));
#ifdef _USE_X11
  Display *display = _ApplicationDisplay(_(ctx).application);
  int screen = _ApplicationScreen(_(ctx).application);

  Arg wargs[10] = {0};
  int n = 0;
  XtSetArg(wargs[n], XtNwidth, _(ctx).size.w); n++;
  XtSetArg(wargs[n], XtNheight, _(ctx).size.h); n++;

  Widget w = XtCreatePopupShell("temp", shellWidgetClass,
    _ApplicationToplevel(_(ctx).application), wargs, n);

  n = 0;
  XtSetArg(wargs[n], XtNbackground, ColorXColor(ColorRgb(250, 250, 250)).pixel); n++;
  Widget f = XtCreateManagedWidget("form", compositeWidgetClass, w, wargs, n);
  XtPopup(w, XtGrabNone);
  _(ctx).internal = f;

  _(ctx).win = w;
  _(ctx).window = XtWindow(w);
  _(ctx).gc = DefaultGC(display, screen);

  XSelectInput(display, _(ctx).window,
    ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask);

  _(ctx).deleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(display, _(ctx).window, &_(ctx).deleteMessage, 1);
#endif
}

ref(Widget) _WidgetCreate(ref(Widget) parent, const char *name)
{
  ref(Widget) rtn = allocate(Widget);

  _(rtn).children = vector_new(ref(Widget));
  _(rtn).flowProcessor = _FlowProcessorCreate();
  _(rtn).background = ColorRgb(WIDGET_COLOR);
  _(rtn).border = 1;
  _(rtn).type = sstream_new_cstr(name);

  if(parent)
  {
    _(rtn).size = SizeWh(32, 32);
    _(rtn).bounds = RectXywh(0, 0, _(rtn).size.w, _(rtn).size.h);
    _(rtn).parent = parent;
    _(rtn).application = _(parent).application;
    vector_push(_(parent).children, rtn);
  }
  else
  {
    _(rtn).size = SizeWh(256, 256);
    _(rtn).bounds = RectXywh(0, 0, _(rtn).size.w, _(rtn).size.h);
    _(rtn).application = _application;
    _ApplicationAddWidget(_application, rtn);
    _WidgetCreateWindow(rtn);
    _(rtn).graphics = _GraphicsCreate(rtn);
  }

  return rtn;
}

void _WidgetSetEventTable(ref(Widget) ctx, struct EventTable *events)
{
  _(ctx).events = *events;
}

void _WidgetSetUserData(ref(Widget) ctx, refvoid userData)
{
  _(ctx).userData = userData;
}

refvoid _WidgetUserData(ref(Widget) ctx)
{
  return _(ctx).userData;
}

void _WidgetInit(ref(Widget) ctx)
{
  struct InitEvent ev = {0};

  ev.sender = ctx;
  _(ctx).events.init(&ev);
}

ref(Application) WidgetApplication(ref(Widget) ctx)
{
  return _(ctx).application;
}

void _WidgetDestroy(ref(Widget) ctx)
{
  foreach(ref(Widget) w, _(ctx).children,
    _WidgetDestroy(w);
  )

  vector_delete(_(ctx).children);
  _FlowProcessorDestroy(_(ctx).flowProcessor);

  if(_(ctx).userData)
  {
    release(_(ctx).userData);
  }

  if(_(ctx).graphics)
  {
    _GraphicsDestroy(_(ctx).graphics);
  }

  if(!_(ctx).parent)
  {
#ifdef _USE_X11
    // TODO
    // XDestroyWindow(_ApplicationDisplay(_(ctx).application), _(ctx).window);
    XtDestroyWidget(_(ctx).win);
#endif
  }

  sstream_delete(_(ctx).type);
  release(ctx);
}

int _WidgetDestroyed(ref(Widget) ctx)
{
  return _(ctx).destroyed;
}

void WidgetDestroy(ref(Widget) ctx)
{
  if(!_(ctx).destroyed)
  {
    foreach(ref(Widget) w, _(ctx).children,
      WidgetDestroy(w);
    )

    struct DestroyEvent ev = {0};
    ev.sender = ctx;
    _(ctx).events.destroy(&ev);
    _(ctx).destroyed = 1;
  }
}

struct Rect WidgetBounds(ref(Widget) ctx)
{
  return _(ctx).bounds;
}

void _WidgetSetBounds(ref(Widget) ctx, struct Rect bounds)
{
  _(ctx).bounds = bounds;
}

struct Size WidgetSize(ref(Widget) ctx)
{
  return _(ctx).size;
}

void WidgetSetSize(ref(Widget) ctx, struct Size size)
{
  _(ctx).size = size;

  // Dont actually resize widgets, just flag for resize
  _ApplicationRequestResize(WidgetApplication(ctx));

  // If dealing with the actual window, then resize that.
  if(!_(ctx).parent)
  {
    XtResizeWidget(_(ctx).win, _(ctx).size.w, _(ctx).size.h, 0);
  }

/*
#ifdef USE_X11
  if(!_(ctx).parent)
  {
    XtResizeWidget(_(ctx).win, _(ctx).size.w, _(ctx).size.h, 0);
  }
  else
  {
    XtResizeWidget(_(ctx).internal, _(ctx).size.w, _(ctx).size.h, 1);
  }
#endif
*/
}

void WidgetSetWidth(ref(Widget) ctx, int width)
{
  _(ctx).size.w = width;

/*
#ifdef USE_X11
  if(!_(ctx).parent)
  {
    XtResizeWidget(_(ctx).win, _(ctx).size.w, _(ctx).size.h, 0);
  }
  else
  {
    XtResizeWidget(_(ctx).internal, _(ctx).size.w, _(ctx).size.h, 1);
  }
#endif
*/
}

void WidgetSetHeight(ref(Widget) ctx, int height)
{
  _(ctx).size.h = height;

/*
#ifdef USE_X11
  if(!_(ctx).parent)
  {
    XtResizeWidget(_(ctx).win, _(ctx).size.w, _(ctx).size.h, 0);
  }
  else
  {
    XtResizeWidget(_(ctx).internal, _(ctx).size.w, _(ctx).size.h, 1);
  }
#endif
*/
}

void _WidgetResize(ref(Widget) ctx, struct Size size)
{
  struct ResizeEvent ev = {0};
  ev.sender = ctx;
  ev.size = size;
  _(ctx).events.resize(&ev);
  _(ctx).bounds.w = size.w;
  _(ctx).bounds.h = size.h;

  _FlowProcessorReset(_(ctx).flowProcessor, _(ctx).bounds, _(ctx).children);

  foreach(ref(Widget) w, _(ctx).children,
    _WidgetResize(w, SizeWh(_(w).bounds.w, _(w).bounds.h));
  )
}

ref(Widget) WidgetRoot(ref(Widget) ctx)
{
  ref(Widget) rtn = ctx;

  while(1)
  {
    if(!WidgetParent(rtn))
    {
      break;
    }

    rtn = WidgetParent(rtn);
  }

  return rtn;
}

void _WidgetDraw(ref(Widget) ctx, struct Rect rect)
{
  ref(Widget) root = WidgetRoot(ctx);
  ref(Graphics) g = _(root).graphics;
  struct DrawEvent ev = {0};

  /*
   * First expose happens before a resize so make sure to position children
   * before this first draw. Resize begins a draw anyway so return here so
   * not to redraw twice.
   */
  if(_(ctx).graphics)
  {
    if(!_(ctx).drawn)
    {
      _(ctx).drawn = 1;
      _WidgetResize(ctx, RectSize(_(ctx).bounds));

      return;
    }
  }

  _GraphicsSetClip(g, rect);
  GraphicsFillRect(g, _(ctx).bounds, ColorRgb(225, 225, 225));

  ev.sender = ctx;
  ev.graphics = g;
  _(ctx).events.draw(&ev);

  foreach(ref(Widget) w, _(ctx).children,
    _WidgetDraw(w, rect);
  )
}

void WidgetFlow(ref(Widget) ctx, char *str)
{
  ref(sstream) s = sstream_new_cstr(str);
  int mod = 0;
  ref(Widget) parent = WidgetParent(ctx);

  {size_t i = 0; for(; i < sstream_length(s); i++)
  {
    char c = sstream_at(s, i);

    if(c == '=')
    {
      mod = 10;
      continue;
    }
    else if(c == '/')
    {
      mod = 100;
      continue;
    }
    else if(c == '^')
    {
      _FlowProcessorAddInstruction(_(parent).flowProcessor, ctx,
        FLOW_MOVE_UP + mod);
    }
    else if(c == 'v')
    {
      _FlowProcessorAddInstruction(_(parent).flowProcessor, ctx,
        FLOW_MOVE_DOWN + mod);
    }
    else if(c == '<')
    {
      _FlowProcessorAddInstruction(_(parent).flowProcessor, ctx,
        FLOW_MOVE_LEFT + mod);
    }
    else if(c == '>')
    {
      _FlowProcessorAddInstruction(_(parent).flowProcessor, ctx,
        FLOW_MOVE_RIGHT + mod);
    }

    mod = 0;
  }}

  sstream_delete(s);
}

ref(Widget) WidgetParent(ref(Widget) ctx)
{
  return _(ctx).parent;
}

struct Color WidgetBackground(ref(Widget) ctx)
{
  return _(ctx).background;
}

void WidgetSetBackground(ref(Widget) ctx, struct Color background)
{
  _(ctx).background = background;
}

void WidgetSetBorder(ref(Widget) ctx, int border)
{
  _(ctx).border = border;
}

int WidgetBorder(ref(Widget) ctx)
{
  return _(ctx).border;
}

#ifdef USE_X11
Window _WidgetWindow(ref(Widget) ctx)
{
  //return _(ctx).window;
  return XtWindow(_(ctx).win);
}

GC _WidgetGc(ref(Widget) ctx)
{
  return _(ctx).gc;
}

Atom _WidgetDeleteMessage(ref(Widget) ctx)
{
  return _(ctx).deleteMessage;
}

void _WidgetSetInternal(ref(Widget) ctx, Widget internal)
{
  _(ctx).internal = internal;
}

Widget _WidgetInternal(ref(Widget) ctx)
{
  return _(ctx).internal;
}

#endif

