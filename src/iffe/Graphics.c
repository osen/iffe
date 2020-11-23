#include "Graphics.h"
#include "Rect.h"
#include "Color.h"
#include "Widget.h"
#include "Application.h"

#ifdef USE_X11
  #include <X11/Xlib.h>
#endif

struct Graphics
{
  ref(Widget) widget;
  struct Rect clip;
};

#ifdef USE_X11
static Display *_GraphicsDisplay(ref(Graphics) ctx)
{
  ref(Application) a = WidgetApplication(_(ctx).widget);

  return _ApplicationDisplay(a);
}

static int _GraphicsWindow(ref(Graphics) ctx)
{
  return _WidgetWindow(_(ctx).widget);
}

static GC _GraphicsGc(ref(Graphics) ctx)
{
  return _WidgetGc(_(ctx).widget);
}
#endif

ref(Graphics) _GraphicsCreate(ref(Widget) widget)
{
  ref(Graphics) rtn = allocate(Graphics);

  _(rtn).widget = widget;

  return rtn;
}

void _GraphicsDestroy(ref(Graphics) ctx)
{
  release(ctx);
}

void _GraphicsSetClip(ref(Graphics) ctx, struct Rect clip)
{
  _(ctx).clip = clip;
}

void GraphicsFillRect(ref(Graphics) ctx, struct Rect rect, struct Color color)
{
  XSetForeground(_GraphicsDisplay(ctx), _GraphicsGc(ctx), ColorXColor(color).pixel);

  XFillRectangle(_GraphicsDisplay(ctx),
    _GraphicsWindow(ctx),
    _GraphicsGc(ctx), rect.x, rect.y, rect.w, rect.h);
}

void GraphicsDrawRect(ref(Graphics) ctx, struct Rect rect, struct Color color)
{
  rect.w -= 1;
  rect.h -= 1;

  XSetForeground(_GraphicsDisplay(ctx), _GraphicsGc(ctx), ColorXColor(color).pixel);

  XDrawRectangle(_GraphicsDisplay(ctx),
    _GraphicsWindow(ctx),
    _GraphicsGc(ctx), rect.x, rect.y, rect.w, rect.h);
}

void GraphicsRaisedRect(ref(Graphics) ctx, struct Rect rect, struct Color color)
{
  struct Rect l = {0};

  GraphicsFillRect(ctx, rect, color);
  GraphicsDrawRect(ctx, rect, ColorLight(color));

  l.x = rect.x;
  l.y = rect.y + rect.h - 1;
  l.w = rect.x + rect.w - 1;
  l.h = l.y;
  GraphicsDrawLine(ctx, l, ColorDark(color));

  l.x = rect.x + rect.w - 1;
  l.y = rect.y;
  l.w = l.x;
  l.h = rect.y + rect.h - 1;
  GraphicsDrawLine(ctx, l, ColorDark(color));
}

void GraphicsDrawLine(ref(Graphics) ctx, struct Rect rect, struct Color color)
{
  XSetForeground(_GraphicsDisplay(ctx), _GraphicsGc(ctx), ColorXColor(color).pixel);

  XDrawLine(_GraphicsDisplay(ctx), _GraphicsWindow(ctx), _GraphicsGc(ctx),
    rect.x, rect.y, rect.w, rect.h);
}
