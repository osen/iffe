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

struct Rect RectAdd(struct Rect a, struct Rect b)
{
  struct Rect rtn = a;

  rtn.x += b.x;
  rtn.y += b.y;
  rtn.w += b.w;
  rtn.h += b.h;

  return rtn;
}
