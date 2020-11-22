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

void GraphicsFillRect(ref(Graphics) ctx, struct Rect rect, struct Color color)
{
  XSetForeground(_GraphicsDisplay(ctx), _GraphicsGc(ctx), ColorXColor(color).pixel);

  XFillRectangle(_GraphicsDisplay(ctx),
    _GraphicsWindow(ctx),
    _GraphicsGc(ctx), rect.x, rect.y, rect.w, rect.h);
}

