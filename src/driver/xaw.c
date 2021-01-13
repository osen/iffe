#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>

static Display *display;
static int screen;
static XtAppContext context;
static Widget toplevel;

static char *fallback_resources[] = {
  NULL
};

void _initialize(int argc, char *argv[])
{
  toplevel = XtAppInitialize(&context, "Xtodo", NULL, 0,
    &argc, argv, fallback_resources, NULL, 0);

  display = XtDisplay(toplevel);
  screen = DefaultScreen(display);
}

