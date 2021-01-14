#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <X11/StringDefs.h>

#include <stdlib.h>
#include <stdio.h>

struct State
{
  Display *display;
  int screen;
  XtAppContext context;
  Atom deleteMessage;
  Widget toplevel;

  struct Widget *widgets;
};

struct Widget
{
  struct Widget *next;

  Widget widget;
  void *userdata;

  Widget windowWidget;
  Window window;
  int destroyed;

  void (*destroyFunc)(void *);
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

  rtn->deleteMessage = XInternAtom(rtn->display, "WM_DELETE_WINDOW", False);

  return rtn;
}

void cleanup(void *state)
{
  struct State *s = state;

  // TODO

  free(s);
}

static void window_destroy_cb(Widget _w, XtPointer cd, XtPointer ud)
{
  struct Widget *w = cd;

  if(w->destroyFunc)
  {
    w->destroyFunc(w);
  }
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

  rtn->windowWidget = w;
  rtn->window = XtWindow(w);
  rtn->widget = f;

  XSelectInput(s->display, rtn->window,
    ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask |
    StructureNotifyMask);

  XSetWMProtocols(s->display, rtn->window, &s->deleteMessage, 1);

  XtAddCallback(f, XtNdestroyCallback, window_destroy_cb, rtn);

  rtn->next = s->widgets;
  s->widgets = rtn;

  return rtn;
}

void run(void *state)
{
  struct State *s = state;
  XEvent e = {0};

  while(!XtAppGetExitFlag(s->context))
  {
    while(XtAppPending(s->context))
    {
      XtAppNextEvent(s->context, &e);

      if(e.type == ClientMessage)
      {
        if(e.xclient.data.l[0] == s->deleteMessage)
        {
          struct Widget *w = s->widgets;

          while(w)
          {
            if(w->window == e.xany.window)
            {
              w->destroyed = 1;
            }

            w = w->next;
          }
        }
      }

      XtDispatchEvent(&e);
    }

    struct Widget *w = s->widgets;
    struct Widget **l = &s->widgets;

    while(w)
    {
      if(w->destroyed)
      {
        struct Widget *dw = w;
        *l = w->next;
        w = w->next;
        XtDestroyWidget(dw->windowWidget);
        free(dw);
      }
      else
      {
        l = &w->next;
        w = w->next;
      }
    }

    if(!s->widgets) break;
  }
}

