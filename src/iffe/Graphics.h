#include "stent.h"

struct Graphics;
struct Rect;
struct Color;
struct Widget;

ref(Graphics) _GraphicsCreate(ref(Widget) widget);
void _GraphicsDestroy(ref(Graphics) ctx);

void GraphicsFillRect(ref(Graphics) ctx, struct Rect rect, struct Color color);

