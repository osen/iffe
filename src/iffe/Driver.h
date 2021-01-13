#include "stent.h"

ref(Driver) DriverCreate();
void DriverDestroy(ref(Driver) ctx);

void *DriverInitialize(ref(Driver) ctx, int argc, char *argv[]);
void *DriverCreateWindow(ref(Driver) ctx);
