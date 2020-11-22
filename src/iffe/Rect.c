#include "Rect.h"

struct Rect RectXywh(int x, int y, int w, int h)
{
  struct Rect rtn = {0};

  rtn.x = x;
  rtn.y = y;
  rtn.w = w;
  rtn.h = h;

  return rtn;
}

