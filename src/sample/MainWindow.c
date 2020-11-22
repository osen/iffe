#include <iffe/iffe.h>

#include <stdio.h>

widget(MainWindow, Init Resize Draw)
{
  int dummy;
};

void OnInit(struct InitEvent *event)
{
  printf("OnInit\n");
}

void OnResize(struct ResizeEvent *event)
{
  printf("OnResize\n");
}

void OnDraw(struct DrawEvent *event)
{
  ref(Graphics) g = event->graphics;

  printf("OnDraw\n");
  GraphicsFillRect(g, RectXywh(10, 10, 100, 100), ColorRgb(255, 0, 0));
}

