#include "stent.h"
#include "config.h"

#ifdef USE_X11
  #include <X11/Xlib.h>
  #include <X11/Intrinsic.h>
#endif

struct Application;
struct Driver;
struct Widget;

ref(Application) _ApplicationCreate(int argc, char *argv[]);
void _ApplicationDestroy(ref(Application) ctx);

void _ApplicationRun(ref(Application) ctx);

void _ApplicationAddWidget(ref(Application) ctx, ref(Widget) widget);
void _ApplicationRequestResize(ref(Application) ctx);
ref(Driver) ApplicationDriver(ref(Application) ctx);

#ifdef USE_X11
Display *_ApplicationDisplay(ref(Application) ctx);
int _ApplicationScreen(ref(Application) ctx);
Widget _ApplicationToplevel(ref(Application) ctx);
XtAppContext _ApplicationContext(ref(Application) ctx);
#endif
