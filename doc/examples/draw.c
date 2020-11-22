#include <iffe/iffe.h>

widget(MainWindow, Draw)
{
  int dummy;
};

void OnDraw(struct DrawEvent *e)
{
  ref(Graphics) g = e->graphics;

  GraphicsFillRect(g, RectXywh(10, 10, 100, 100), ColorRgb(255, 0, 0));
}

