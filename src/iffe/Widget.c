#include "Widget.h"
#include "events.h"
#include "Application.h"
#include "Size.h"
#include "Rect.h"
#include "Graphics.h"
#include "Color.h"

struct Widget
{
  ref(Application) application;
  ref(Widget) parent;
  vector(ref(Widget)) children;
  struct EventTable events;
  refvoid userData;
  int destroyed;
  ref(sstream) type;
  struct Rect bounds;
  ref(Graphics) graphics;

#ifdef USE_X11
  Window window;
  Atom deleteMessage;
  GC gc;
#endif
};

ref(Widget)_widgetLastWidget;
extern ref(Application) _application;

static void _WidgetCreateWindow(ref(Widget) ctx)
{
#ifdef USE_X11
  Display *display = _ApplicationDisplay(_(ctx).application);
  int screen = _ApplicationScreen(_(ctx).application);

  _(ctx).window = XCreateWindow(display, RootWindow(display, screen),
    0, 0, _(ctx).bounds.w, _(ctx).bounds.h, 0, 0,
    CopyFromParent, CopyFromParent,
    0, NULL);

  _(ctx).gc = DefaultGC(display, screen);

  XSelectInput(display, _(ctx).window,
    ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask);

  _(ctx).deleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(display, _(ctx).window, &_(ctx).deleteMessage, 1);

  XMapWindow(display, _(ctx).window);
#endif
}

ref(Widget) _WidgetCreate(ref(Widget) parent, const char *name)
{
  ref(Widget) rtn = allocate(Widget);

  _(rtn).children = vector_new(ref(Widget));

  if(parent)
  {
    _(rtn).bounds = RectXywh(0, 0, 32, 32);
    _(rtn).parent = parent;
    _(rtn).application = _(parent).application;
    vector_push(_(parent).children, rtn);
  }
  else
  {
    _(rtn).bounds = RectXywh(0, 0, 256, 256);
    _(rtn).application = _application;
    _ApplicationAddWidget(_application, rtn);
    _WidgetCreateWindow(rtn);
    _(rtn).graphics = _GraphicsCreate(rtn);
  }

  _(rtn).type = sstream_new_cstr(name);

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
#ifdef USE_X11
    XDestroyWindow(_ApplicationDisplay(_(ctx).application), _(ctx).window);
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
    struct DestroyEvent ev = {0};
    ev.sender = ctx;
    _(ctx).events.destroy(&ev);
    _(ctx).destroyed = 1;

    foreach(ref(Widget) w, _(ctx).children,
      WidgetDestroy(w);
    )
  }
}

struct Size WidgetSize(ref(Widget) ctx)
{
  struct Size rtn = {0};

  rtn.w = _(ctx).bounds.w;
  rtn.h = _(ctx).bounds.h;

  return rtn;
}

void WidgetSetSize(ref(Widget) ctx, struct Size size)
{
  _(ctx).bounds.w = size.w;
  _(ctx).bounds.h = size.h;
}

void _WidgetResize(ref(Widget) ctx, struct Size size)
{
  struct ResizeEvent ev = {0};
  ev.sender = ctx;
  ev.size = size;
  _(ctx).events.resize(&ev);
  _(ctx).bounds.w = size.w;
  _(ctx).bounds.h = size.h;
}

void _WidgetDraw(ref(Widget) ctx, struct Rect rect)
{
  struct DrawEvent ev = {0};
  ev.sender = ctx;
  ev.graphics = _(ctx).graphics;

  _GraphicsSetClip(_(ctx).graphics, rect);
  GraphicsFillRect(_(ctx).graphics, _(ctx).bounds, ColorRgb(225, 225, 225));

  _(ctx).events.draw(&ev);

  foreach(ref(Widget) w, _(ctx).children,
    ev.sender = w;
    _(w).events.draw(&ev);
  )
}

struct Rect WidgetBounds(ref(Widget) ctx)
{
  return _(ctx).bounds;
}

#ifdef USE_X11
Window _WidgetWindow(ref(Widget) ctx)
{
  return _(ctx).window;
}

GC _WidgetGc(ref(Widget) ctx)
{
  return _(ctx).gc;
}

Atom _WidgetDeleteMessage(ref(Widget) ctx)
{
  return _(ctx).deleteMessage;
}
#endif

