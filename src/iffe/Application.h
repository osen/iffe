#include "stent.h"
#include "Widget.h"

#define ApplicationAdd(A, T)                  \
  _widgetLastWidget = _ApplicationAdd(A, #T); \
  do                                          \
  {                                           \
    void _##T##Init(ref(Widget) ctx);         \
    ref(Widget) w = _widgetLastWidget;        \
    _widgetLastWidget = NULL;                 \
    if(!w) panic("Invalid construct");        \
    _##T##Init(w);                            \
    _WidgetInit(w);                           \
  }                                           \
  while(0)

struct Application;

ref(Application) _ApplicationCreate();
void _ApplicationDestroy(ref(Application) ctx);

void _ApplicationRun(ref(Application) ctx);
ref(Widget) _ApplicationAdd(ref(Application) ctx, const char *name);

