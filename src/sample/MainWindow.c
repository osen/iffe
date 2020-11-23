#include <iffe/iffe.h>

#include <stdio.h>

widget(MainWindow, Init Resize Draw)
{
  int dummy;
};

void OnInit(struct InitEvent *ev)
{
  printf("OnInit\n");

  ref(Widget) panel = WidgetAdd(ev->sender, Spacer);
  WidgetSetHeight(panel, 100);
  WidgetFlow(panel, "^=<");

  ref(Widget) w = WidgetAdd(panel, Button);
  WidgetFlow(w, "^<");

  w = WidgetAdd(panel, Button);
  WidgetFlow(w, ">");

  ref(Widget) sw = WidgetAdd(ev->sender, Spacer);
  WidgetFlow(sw, "=<^");

  w = WidgetAdd(ev->sender, Button);
  WidgetFlow(w, ">");

  WidgetFlow(sw, "v");
}

void OnResize(struct ResizeEvent *ev)
{
  printf("OnResize\n");
}

void OnDraw(struct DrawEvent *ev)
{
  printf("OnDraw\n");
}

