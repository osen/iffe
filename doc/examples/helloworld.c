#include <iffe/iffe.h>

widget(MainWindow, Init)
{
  int dummy;
};

void OnInit(struct InitEvent *e)
{
  ref(Widget) label = WidgetAdd(e->sender, Label);
  LabelSetText(label, "Hello World!");
}

