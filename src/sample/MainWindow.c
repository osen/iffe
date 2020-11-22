#include <iffe/iffe.h>

#include <stdio.h>

widget(MainWindow, Init Resize Draw)
{
  int dummy;
};

void OnInit(struct InitEvent *ev)
{
  printf("OnInit\n");
  ref(Widget) close = WidgetAdd(ev->sender, Button);
  WidgetFlow(close, "^<");

  ref(Widget) next = WidgetAdd(ev->sender, Button);
  WidgetFlow(next, "^>");
}

void OnResize(struct ResizeEvent *ev)
{
  printf("OnResize\n");
}

void OnDraw(struct DrawEvent *ev)
{
  printf("OnDraw\n");
}

