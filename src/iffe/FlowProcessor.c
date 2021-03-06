#include "FlowProcessor.h"
#include "Widget.h"
#include "Rect.h"
#include "Size.h"

#include <stdio.h>

struct FlowInstruction
{
  ref(Widget) widget;
  int instruction;
};

struct FlowProcessor
{
  vector(struct FlowInstruction) instructions;
  struct Size size;
  vector(ref(Widget)) children;
};

ref(FlowProcessor) _FlowProcessorCreate()
{
  ref(FlowProcessor) rtn = allocate(FlowProcessor);
  _(rtn).instructions = vector_new(struct FlowInstruction);

  return rtn;
}

void _FlowProcessorDestroy(ref(FlowProcessor) ctx)
{
  vector_delete(_(ctx).instructions);
  release(ctx);
}

void _FlowProcessorAddInstruction(ref(FlowProcessor) ctx,
  ref(Widget) widget, int instruction)
{
  struct FlowInstruction fi = {0};

  fi.widget = widget;
  fi.instruction = instruction;

  vector_push(_(ctx).instructions, fi);
}

static int _FlowProcessorColliding(ref(FlowProcessor) ctx, ref(Widget) widget, struct Rect a)
{
  if(a.x < 0) return 1;
  if(a.x + a.w > _(ctx).size.w) return 1;
  if(a.y < 0) return 1;
  if(a.y + a.h > _(ctx).size.h) return 1;

  foreach(ref(Widget) w, _(ctx).children,
    struct Rect b = WidgetBounds(w);

    if(w == widget) continue;
    if(b.x < 0) continue;

    if(a.x < b.x)
    {
      if(a.x + a.w <= b.x) continue;
    }
    else
    {
      if(b.x + b.w <= a.x) continue;
    }

    if(a.y < b.y)
    {
      if(a.y + a.h <= b.y) continue;
    }
    else
    {
      if(b.y + b.h <= a.y) continue;
    }

    return 1;
  )

  return 0;
}

static void _FlowProcessorProcess(ref(FlowProcessor) ctx, struct FlowInstruction instruction)
{
  ref(Widget) w = instruction.widget;
  struct Rect bounds = WidgetBounds(w);
  struct Rect delta = {0};
  struct Rect orig = {0};
  int center = 0;

  bounds.x -= 4;
  bounds.y -= 4;
  bounds.w += 8;
  bounds.h += 8;

  if(bounds.x < 0)
  {
    bounds.x = _(ctx).size.w - bounds.w;
    bounds.y = _(ctx).size.h - bounds.h;
  }

  orig = bounds;

  if(instruction.instruction == FLOW_CENTER_UP ||
    instruction.instruction == FLOW_CENTER_DOWN ||
    instruction.instruction == FLOW_CENTER_LEFT ||
    instruction.instruction == FLOW_CENTER_RIGHT)
  {
    center = 1;
  }

  if(instruction.instruction == FLOW_MOVE_UP ||
    instruction.instruction == FLOW_CENTER_UP)
  {
    delta.y--;
  }
  else if(instruction.instruction == FLOW_MOVE_DOWN ||
    instruction.instruction == FLOW_CENTER_DOWN)
  {
    delta.y++;
  }
  else if(instruction.instruction == FLOW_MOVE_LEFT ||
    instruction.instruction == FLOW_CENTER_LEFT)
  {
    delta.x--;
  }
  else if(instruction.instruction == FLOW_MOVE_RIGHT ||
    instruction.instruction == FLOW_CENTER_RIGHT)
  {
    delta.x++;
  }
  else if(instruction.instruction == FLOW_EXPAND_UP)
  {
    delta.y--;
    delta.h++;
  }
  else if(instruction.instruction == FLOW_EXPAND_DOWN)
  {
    delta.h++;
  }
  else if(instruction.instruction == FLOW_EXPAND_LEFT)
  {
    delta.x--;
    delta.w++;
  }
  else if(instruction.instruction == FLOW_EXPAND_RIGHT)
  {
    delta.w++;
  }

  while(1)
  {
    struct Rect tb = RectAdd(bounds, delta);

    if(_FlowProcessorColliding(ctx, w, tb))
    {
      break;
    }

    bounds = tb;
  }

  if(center)
  {
    bounds.x = (bounds.x + orig.x) / 2;
    bounds.y = (bounds.y + orig.y) / 2;
  }

  bounds.x += 4;
  bounds.y += 4;
  bounds.w -= 8;
  bounds.h -= 8;
  _WidgetSetBounds(w, bounds);
}

void _FlowProcessorReset(ref(FlowProcessor) ctx, struct Rect bounds, vector(ref(Widget)) children)
{
  struct Size size = SizeWh(bounds.w, bounds.h);
  _(ctx).size = size;
  _(ctx).children = children;

  foreach(ref(Widget) w, children,
    struct Rect bounds = WidgetBounds(w);
    bounds.w = WidgetSize(w).w;
    bounds.h = WidgetSize(w).h;
    bounds.x = -bounds.w;
    bounds.y = -bounds.h;
    _WidgetSetBounds(w, bounds);
  )

  foreach(struct FlowInstruction fi, _(ctx).instructions,
    _FlowProcessorProcess(ctx, fi);
  )

  foreach(ref(Widget) w, children,
    struct Rect b = WidgetBounds(w);
    //b.x += bounds.x;
    //b.y += bounds.y;
    b.w -= WidgetBorder(w) * 2;
    b.h -= WidgetBorder(w) * 2;
    _WidgetSetBounds(w, b);
  )

/*
  foreach(ref(Widget) w, children,
    struct Rect bounds = WidgetBounds(w);

    if(bounds.x < 0)
    {
      bounds.x = 0;
      bounds.y = 0;
      _WidgetSetBounds(w, bounds);
    }
  )
*/
}

