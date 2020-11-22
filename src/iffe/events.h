#include "stent.h"

#define EVENT_COMMON \
  ref(Widget) sender

struct Widget;

struct InitEvent
{
  EVENT_COMMON;
};

struct ResizeEvent
{
  EVENT_COMMON;
};

struct DrawEvent
{
  EVENT_COMMON;
};

struct ClickEvent
{
  EVENT_COMMON;
};

struct DestroyEvent
{
  EVENT_COMMON;
};

struct EventTable
{
  void (*init)(struct InitEvent *);
  void (*resize)(struct ResizeEvent *);
  void (*draw)(struct DrawEvent *);
  void (*click)(struct ClickEvent *);
  void (*destroy)(struct DestroyEvent *);
};

