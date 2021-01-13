#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <X11/StringDefs.h>

#include <stdlib.h>

struct State
{
  Display *display;
  int screen;
  XtAppContext context;
  Widget toplevel;
};

struct Widget
{
  Widget widget;

  Widget window;
  Atom deleteMessage;
};

static char *fallback_resources[] = {
  NULL
};

void *initialize(int argc, char *argv[])
{
  struct State *rtn = calloc(1, sizeof(*rtn));

  rtn->toplevel = XtAppInitialize(&rtn->context, "Xtodo", NULL, 0,
    &argc, argv, fallback_resources, NULL, 0);

  rtn->display = XtDisplay(rtn->toplevel);
  rtn->screen = DefaultScreen(rtn->display);

  return rtn;
}

void cleanup(void *state)
{
  struct State *s = state;

  // TODO

  free(s);
}

void *create_window(void *state)
{
  struct State *s = state;
  Arg wargs[10] = {0};
  int n = 0;
  struct Widget *rtn = calloc(1, sizeof(*rtn));

  XtSetArg(wargs[n], XtNwidth, 320); n++;
  XtSetArg(wargs[n], XtNheight, 240); n++;

  Widget w = XtCreatePopupShell("shell", shellWidgetClass,
    s->toplevel, wargs, n);

  Widget f = XtCreateManagedWidget("composite", compositeWidgetClass, w,
    NULL, 0);

  XtPopup(w, XtGrabNone);

  rtn->window = w;
  rtn->widget = f;

  rtn->deleteMessage = XInternAtom(s->display, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(s->display, XtWindow(rtn->window), &rtn->deleteMessage, 1);

  return rtn;
}

