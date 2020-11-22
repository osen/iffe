#include <iffe/iffe.h>

widget(MainWindow, Init)
{
  int dummy;
};

void OnInit(struct InitEvent *ev)
{
  ref(Widget) p1 = WidgetAdd(ev->sender, Panel);
  WidgetSetHeight(p1, 200);
  WidgetAddFlow(p1, "^=<");
  ref(Button) b1 = WidgetAdd(p1, Button);

  ref(Widget) p2 = WidgetAdd(ev->sender, Panel);
  WidgetSetHeight(p2, 200);
  WidgetAddFlow(p2, "=<");
  ref(Button) b2 = WidgetAdd(p2, Button);
}

