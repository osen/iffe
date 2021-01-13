#include <iffe/iffe.h>

widget(LoginWindow, Init)
{
  int dummy;
};

void OnInit(struct InitEvent *ev)
{
  WidgetSetSize(ev->sender, SizeWh(640, 480));

  ref(Widget) panel = WidgetAdd(ev->sender, Panel);
  WidgetSetSize(panel, SizeWh(320, 240));
  WidgetFlow(panel, "/</^");

  ref(Widget) w = WidgetAdd(panel, Toggle);
  WidgetFlow(w, "<v");

  ref(Widget) closeButton = WidgetAdd(panel, Button);
  WidgetFlow(closeButton, ">v");
}

