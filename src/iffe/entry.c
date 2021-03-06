#define STENT_IMPLEMENTATION
#include "stent.h"
#include "Application.h"

int _main(int argc, char *argv[])
{
  ref(Application) app = _ApplicationCreate(argc, argv);
  _ApplicationRun(app);
  _ApplicationDestroy(app);

  return 0;
}
