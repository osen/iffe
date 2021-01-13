#include "Widget.h"
#include "Graphics.h"
#include "Color.h"
#include "Rect.h"
#include "Size.h"

#ifdef USE_X11
  #include <X11/Xaw/Label.h>
  #include <X11/IntrinsicP.h>
  #include <X11/StringDefs.h>
#endif

widget(Spacer, Init Resize Draw)
{
  int dummy;
};

void OnInit(struct InitEvent *ev)
{
  WidgetSetSize(ev->sender, SizeWh(1, 1));
  WidgetSetBorder(ev->sender, 0);

#ifdef USE_X11
  Widget p = _WidgetInternal(WidgetParent(ev->sender));

  Arg wargs[10] = {0};
  int n = 0;
  XtSetArg(wargs[n], XtNbackground, ColorXColor(ColorRgb(0, 0, 0)).pixel); n++;
  Widget b = XtCreateManagedWidget("button", labelWidgetClass,
    p, wargs, n);

  _WidgetSetInternal(ev->sender, b);
#endif
}

void OnResize(struct ResizeEvent *ev)
{
  Widget w = _WidgetInternal(ev->sender);
  struct Rect bounds = WidgetBounds(ev->sender);

  XtResizeWidget(w, bounds.w, bounds.h, WidgetBorder(ev->sender));
  XtMoveWidget(w, bounds.x, bounds.y);
}

void OnDraw(struct DrawEvent *ev)
{
/*
  ref(Graphics) g = ev->graphics;

  GraphicsFillRect(g, WidgetBounds(ev->sender), ColorDark(WidgetBackground(ev->sender)));
*/
}

