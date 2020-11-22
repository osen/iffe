#ifndef IFFE_EVENTS_H
#define IFFE_EVENTS_H

#include "stent.h"
#include "Size.h"

#define EVENT_COMMON \
  ref(Widget) sender

struct Widget;
struct Graphics;

struct InitEvent
{
  EVENT_COMMON;
};

struct ResizeEvent
{
  EVENT_COMMON;
  struct Size size;
};

struct DrawEvent
{
  EVENT_COMMON;
  ref(Graphics) graphics;
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

#endif

