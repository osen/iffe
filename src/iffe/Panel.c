#include "Widget.h"
#include "Graphics.h"
#include "Color.h"
#include "Rect.h"
#include "Size.h"

widget(Panel, Draw)
{
  int dummy;
};

void OnDraw(struct DrawEvent *ev)
{
  ref(Graphics) g = ev->graphics;

  GraphicsRaisedRect(g, WidgetBounds(ev->sender), WidgetBackground(ev->sender));
}

