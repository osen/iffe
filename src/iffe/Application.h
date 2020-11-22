#include "stent.h"
#include "Widget.h"

#include "config.h"

#ifdef USE_X11
  #include <X11/Xlib.h>
#endif

struct Application;

ref(Application) _ApplicationCreate();
void _ApplicationDestroy(ref(Application) ctx);

void _ApplicationRun(ref(Application) ctx);

void _ApplicationAddWidget(ref(Application) ctx, ref(Widget) widget);

#ifdef USE_X11
Display *_ApplicationDisplay(ref(Application) ctx);
int _ApplicationScreen(ref(Application) ctx);
#endif
