#include "Size.h"

struct Size SizeWh(int w, int h)
{
  struct Size rtn = {0};

  rtn.w = w;
  rtn.h = h;

  return rtn;
}

