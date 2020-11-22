#include <iffe/iffe.h>

#include <stdio.h>

widget(MainWindow, Init Resize Draw)
{
  int dummy;
};

void OnInit(struct InitEvent *ev)
{
  printf("OnInit\n");
  WidgetAdd(ev->sender, Button);
}

void OnResize(struct ResizeEvent *ev)
{
  printf("OnResize\n");
}

void OnDraw(struct DrawEvent *ev)
{
  printf("OnDraw\n");
}

