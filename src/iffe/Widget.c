#include "Widget.h"
#include "events.h"
#include "Application.h"
#include "Size.h"
#include "Rect.h"
#include "Graphics.h"
#include "Color.h"
#include "FlowProcessor.h"

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

  int destroyed;
  int drawn;

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
    0, 0, _(ctx).size.w, _(ctx).size.h, 0, 0,
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
  _(rtn).flowProcessor = _FlowProcessorCreate();

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

struct Rect WidgetBounds(ref(Widget) ctx)
{
  return _(ctx).bounds;
}

struct Size WidgetSize(ref(Widget) ctx)
{
  return _(ctx).size;
}

void WidgetSetSize(ref(Widget) ctx, struct Size size)
{
  _(ctx).size = size;
}

void _WidgetResize(ref(Widget) ctx, struct Size size)
{
  struct ResizeEvent ev = {0};
  ev.sender = ctx;
  ev.size = size;
  _(ctx).events.resize(&ev);
  _(ctx).bounds.w = size.w;
  _(ctx).bounds.h = size.h;

  /* Reset FlowProcessor to new size */
  /* Update all child bounds based on LayoutProcessor */
  /* Propagate resize event to each child */

  foreach(ref(Widget) w, _(ctx).children,
    _WidgetResize(w, WidgetSize(w));
  )
}

void _WidgetDraw(ref(Widget) ctx, struct Rect rect)
{
  struct DrawEvent ev = {0};
  ev.sender = ctx;
  ev.graphics = _(ctx).graphics;

  if(!_(ctx).drawn)
  {
    _WidgetResize(ctx, _(ctx).size);
    _(ctx).drawn = 1;
  }

  _GraphicsSetClip(_(ctx).graphics, rect);
  GraphicsFillRect(_(ctx).graphics, _(ctx).bounds, ColorRgb(225, 225, 225));

  _(ctx).events.draw(&ev);

  foreach(ref(Widget) w, _(ctx).children,
    ev.sender = w;
    _(w).events.draw(&ev);
  )
}

void WidgetFlow(ref(Widget) ctx, char *str)
{
  ref(sstream) s = sstream_new_cstr(str);
  int expand = 0;
  ref(Widget) parent = WidgetParent(ctx);

  {size_t i = 0; for(; i < sstream_length(s); i++)
  {
    char c = sstream_at(s, i);

    if(c == '=')
    {
      expand = 10;
      continue;
    }
    else if(c == '^')
    {
      _FlowProcessorAddInstruction(_(parent).flowProcessor, ctx,
        FLOW_MOVE_UP + expand);
    }
    else if(c == 'v')
    {
      _FlowProcessorAddInstruction(_(parent).flowProcessor, ctx,
        FLOW_MOVE_DOWN + expand);
    }
    else if(c == '<')
    {
      _FlowProcessorAddInstruction(_(parent).flowProcessor, ctx,
        FLOW_MOVE_LEFT + expand);
    }
    else if(c == '>')
    {
      _FlowProcessorAddInstruction(_(parent).flowProcessor, ctx,
        FLOW_MOVE_RIGHT + expand);
    }

    expand = 0;
  }}

  sstream_delete(s);
}

ref(Widget) WidgetParent(ref(Widget) ctx)
{
  return _(ctx).parent;
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

