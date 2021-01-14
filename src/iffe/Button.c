#include "Widget.h"
#include "Graphics.h"
#include "Color.h"
#include "Rect.h"
#include "Size.h"
#include "config.h"
#include "Application.h"

#ifdef USE_X11
  #include <X11/Xaw/Command.h>
  #include <X11/IntrinsicP.h>
  #include <X11/StringDefs.h>
#endif

#include <stdio.h>

widget(Button, Init Resize Draw)
{
  int dummy;
};

void ButtonSetLabel(ref(Widget) ctx, const char *label)
{
  Arg wargs[2] = {0};
  int n = 0;
  XtSetArg(wargs[n], XtNlabel, label); n++;
  XtSetValues(_WidgetInternal(ctx), wargs, n);
}

/*
static void destroy(Widget w, XtPointer cd, XtPointer ud)
{
  printf("Destroyed\n");
}
*/

void OnInit(struct InitEvent *ev)
{
#ifdef USE_X11
  Widget p = _WidgetInternal(WidgetParent(ev->sender));

  Arg wargs[10] = {0};
  int n = 0;
  XtSetArg(wargs[n], XtNlabel, ""); n++;
  //XtSetArg(wargs[n], XtNdestroyCallback, destroy); n++;

  Widget b = XtCreateManagedWidget("button", commandWidgetClass,
    p, wargs, n);

  _WidgetSetInternal(ev->sender, b);

  //XtAddCallback(b, XtNdestroyCallback, destroy, NULL);
#endif

  WidgetSetBackground(ev->sender, ColorRgb(BUTTON_COLOR));
  WidgetSetSize(ev->sender, SizeWh(100, 30));
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
  struct Rect b = WidgetBounds(ev->sender);

  GraphicsRaisedRect(g, b, WidgetBackground(ev->sender));
  //GraphicsDrawRect(g, b, ColorRgb(SELECTED_COLOR));
*/
}

