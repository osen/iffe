#include "Widget.h"
#include "Graphics.h"
#include "Color.h"
#include "Rect.h"
#include "Size.h"

#ifdef USE_X11
  #include <X11/IntrinsicP.h>
  #include <X11/StringDefs.h>
#endif

widget(Panel, Init Resize Draw)
{
  int dummy;
};

void OnInit(struct InitEvent *ev)
{
  WidgetSetBackground(ev->sender, ColorRgb(PANEL_COLOR));

#ifdef USE_X11
  Widget p = _WidgetInternal(WidgetParent(ev->sender));

  Arg wargs[10] = {0};
  int n = 0;
  XtSetArg(wargs[n], XtNwidth, 1); n++;
  XtSetArg(wargs[n], XtNheight, 1); n++;
  Widget b = XtCreateManagedWidget("form", compositeWidgetClass,
    p, wargs, n);

  _WidgetSetInternal(ev->sender, b);
  //XtResizeWidget(b, 20, 20, 1);
  //XtMoveWidget(b, 20, 20);
#endif
}

void OnResize(struct ResizeEvent *ev)
{
  Widget w = _WidgetInternal(ev->sender);
  struct Rect bounds = WidgetBounds(ev->sender);

  XtResizeWidget(w, bounds.w, bounds.h, 1);
  XtMoveWidget(w, bounds.x, bounds.y);
}

void OnDraw(struct DrawEvent *ev)
{
  ref(Graphics) g = ev->graphics;

  GraphicsRaisedRect(g, WidgetBounds(ev->sender), WidgetBackground(ev->sender));
}

