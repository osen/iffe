#include <iffe/iffe.h>

widget(MainWindow, Init)
{
  int dummy;
};

void OnInit(struct InitEvent *ev)
{
  ref(Widget) panel = WidgetAdd(ev->sender, Spacer);
  WidgetSetHeight(panel, 100);
  WidgetFlow(panel, "^=<");

  ref(Widget) w = WidgetAdd(panel, Button);
  WidgetFlow(w, "^<");

  w = WidgetAdd(panel, Button);
  WidgetFlow(w, ">");

  ref(Widget) sw = WidgetAdd(ev->sender, Spacer);
  WidgetFlow(sw, "=<^");

  w = WidgetAdd(ev->sender, Button);
  WidgetFlow(w, ">");

  WidgetFlow(sw, "v");
}

