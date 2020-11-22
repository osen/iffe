#include "FlowProcessor.h"
#include "Widget.h"

struct FlowInstruction
{
  ref(Widget) widget;
  int instruction;
};

struct FlowProcessor
{
  vector(struct FlowInstruction) instructions;
};

ref(FlowProcessor) _FlowProcessorCreate()
{
  ref(FlowProcessor) rtn = allocate(FlowProcessor);

  return rtn;
}

void _FlowProcessorDestroy(ref(FlowProcessor) ctx)
{
  release(ctx);
}

void _FlowProcessorAddInstruction(ref(FlowProcessor) ctx,
  ref(Widget) widget, int instruction)
{

}

