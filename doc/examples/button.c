#include <iffe/iffe.h>

widget(MainWindow, Init)
{
  int dummy;
};

static void OnCloseClicked(struct ClickEvent *e)
{
  ref(Widget) window = WidgetWindow(e->sender);
  WindowClose(window);
}

void OnInit(struct InitEvent *e)
{
  ref(Widget) closeButton = WidgetAdd(e->sender, Button);
  ButtonSetText(closeButton, "Close");
  WidgetAddClickHandler(closeButton, OnCloseClicked);
}

