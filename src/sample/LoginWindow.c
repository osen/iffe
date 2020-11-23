#include <iffe/iffe.h>

widget(LoginWindow, Init)
{
  int dummy;
};

void OnInit(struct InitEvent *ev)
{
  WidgetSetSize(ev->sender, SizeWh(640, 480));

  ref(Widget) panel = WidgetAdd(ev->sender, Panel);
  WidgetSetSize(panel, SizeWh(128, 128));
  WidgetFlow(panel, "/</^");
}

