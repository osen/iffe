#include "Widget.h"
#include "Graphics.h"
#include "Color.h"
#include "Rect.h"
#include "Size.h"

widget(Panel, Init Draw)
{
  int dummy;
};

void OnInit(struct InitEvent *ev)
{
  WidgetSetBackground(ev->sender, ColorRgb(PANEL_COLOR));
}

void OnDraw(struct DrawEvent *ev)
{
  ref(Graphics) g = ev->graphics;

  GraphicsRaisedRect(g, WidgetBounds(ev->sender), WidgetBackground(ev->sender));
}

