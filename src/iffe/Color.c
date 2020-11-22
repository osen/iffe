#include "Color.h"

struct Color ColorRgb(unsigned char r, unsigned char g, unsigned char b)
{
  struct Color rtn = {0};

  rtn.r = r;
  rtn.g = g;
  rtn.b = b;

  return rtn;
}

#ifdef USE_X11
XColor ColorXColor(struct Color ctx)
{
  XColor rtn = {0};

  rtn.pixel = ((255 << 24) |
    (ctx.r << 16) |
    (ctx.g << 8) |
    ctx.b);

  return rtn;
}
#endif

