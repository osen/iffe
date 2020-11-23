#include "Widget.h"
#include "Graphics.h"
#include "Color.h"
#include "Rect.h"
#include "Size.h"

widget(Spacer, Init Draw)
{
  int dummy;
};

void OnInit(struct InitEvent *ev)
{
  WidgetSetSize(ev->sender, SizeWh(1, 1));
}

void OnDraw(struct DrawEvent *ev)
{
  ref(Graphics) g = ev->graphics;

  GraphicsFillRect(g, WidgetBounds(ev->sender), ColorDark(WidgetBackground(ev->sender)));
}

