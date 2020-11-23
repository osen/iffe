#include "Widget.h"
#include "Graphics.h"
#include "Color.h"
#include "Rect.h"
#include "Size.h"
#include "config.h"

widget(Button, Init Draw)
{
  int dummy;
};

void OnInit(struct InitEvent *ev)
{
  WidgetSetBackground(ev->sender, ColorRgb(BUTTON_COLOR));
  WidgetSetSize(ev->sender, SizeWh(100, 30));
}

void OnDraw(struct DrawEvent *ev)
{
  ref(Graphics) g = ev->graphics;
  struct Rect b = WidgetBounds(ev->sender);

  GraphicsRaisedRect(g, b, WidgetBackground(ev->sender));
  //GraphicsDrawRect(g, b, ColorRgb(SELECTED_COLOR));
}

