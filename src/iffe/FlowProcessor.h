#include "stent.h"

#define FLOW_MOVE_UP 1
#define FLOW_MOVE_DOWN 2
#define FLOW_MOVE_LEFT 3
#define FLOW_MOVE_RIGHT 4

#define FLOW_EXPAND_UP 11
#define FLOW_EXPAND_DOWN 12
#define FLOW_EXPAND_LEFT 13
#define FLOW_EXPAND_RIGHT 14

struct FlowProcessor;
struct Widget;
struct Rect;

ref(FlowProcessor) _FlowProcessorCreate();
void _FlowProcessorDestroy(ref(FlowProcessor) ctx);

void _FlowProcessorAddInstruction(ref(FlowProcessor) ctx,
  ref(Widget) widget, int instruction);

void _FlowProcessorReset(ref(FlowProcessor) ctx, struct Rect bounds, vector(ref(Widget)) children);
