#include "stent.h"

struct Application;

ref(Application) _ApplicationCreate();
void _ApplicationDestroy(ref(Application) ctx);

void _ApplicationRun(ref(Application) ctx);

