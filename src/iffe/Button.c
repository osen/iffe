#include "Widget.h"
#include "Graphics.h"
#include "Color.h"
#include "Rect.h"
#include "Size.h"

widget(Button, Init Draw)
{
  int dummy;
};

void OnInit(struct InitEvent *ev)
{
  WidgetSetSize(ev->sender, SizeWh(100, 30));
}

void OnDraw(struct DrawEvent *ev)
{
  ref(Graphics) g = ev->graphics;

  GraphicsFillRect(g, WidgetBounds(ev->sender), ColorRgb(255, 0, 0));
}

