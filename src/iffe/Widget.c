#include "Widget.h"
#include "events.h"
#include "Application.h"

struct Widget
{
  ref(Application) application;
  ref(Widget) parent;
  vector(ref(Widget)) children;
  struct EventTable events;
  refvoid userData;
  int destroyed;
  ref(sstream) type;
};

ref(Widget)_widgetLastWidget;

ref(Widget) _WidgetCreateRoot(ref(Application) app, const char *name)
{
  ref(Widget) rtn = allocate(Widget);

  _(rtn).application = app;
  _(rtn).type = sstream_new_cstr(name);

  return rtn;
}

ref(Widget) _WidgetCreate(ref(Widget) parent, const char *name)
{
  ref(Widget) rtn = allocate(Widget);

  _(rtn).parent = parent;
  _(rtn).type = sstream_new_cstr(name);

  return rtn;
}

void _WidgetSetEventTable(ref(Widget) ctx, struct EventTable *events)
{
  _(ctx).events = *events;
}

void _WidgetSetUserData(ref(Widget) ctx, refvoid userData)
{
  _(ctx).userData = userData;
}

refvoid _WidgetUserData(ref(Widget) ctx)
{
  return _(ctx).userData;
}

void _WidgetInit(ref(Widget) ctx)
{
  struct InitEvent ev = {0};

  ev.sender = ctx;
  _(ctx).events.init(&ev);
}

ref(Application) WidgetApplication(ref(Widget) ctx)
{
  if(_(ctx).application)
  {
    return _(ctx).application;
  }

  return WidgetApplication(_(ctx).parent);
}

void _WidgetDestroy(ref(Widget) ctx)
{
  if(!_(ctx).destroyed)
  {
    struct DestroyEvent ev = {0};
    ev.sender = ctx;
    _(ctx).events.destroy(&ev);
    _(ctx).destroyed = 1;
  }

  if(_(ctx).userData)
  {
    release(_(ctx).userData);
  }

  sstream_delete(_(ctx).type);
  release(ctx);
}

