#include <iffe/iffe.h>

#include <stdio.h>

widget(MainWindow, Init Resize Draw)
{
  int dummy;
};

void OnInit(struct InitEvent *ev)
{
  printf("OnInit\n");
  ref(Widget) w = WidgetAdd(ev->sender, Button);
  WidgetFlow(w, "^<");

  w = WidgetAdd(ev->sender, Button);
  WidgetFlow(w, "^>");

  w = WidgetAdd(ev->sender, Spacer);
  WidgetFlow(w, "=<^");
}

void OnResize(struct ResizeEvent *ev)
{
  printf("OnResize\n");
}

void OnDraw(struct DrawEvent *ev)
{
  printf("OnDraw\n");
}

