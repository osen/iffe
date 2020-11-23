#include "Color.h"
#include "config.h"

static int min(int a, int b)
{
  if(a > b) return b;

  return a;
}

static int max(int a, int b)
{
  if(a < b) return b;

  return a;
}

struct Color ColorRgb(unsigned char r, unsigned char g, unsigned char b)
{
  struct Color rtn = {0};

  rtn.r = r;
  rtn.g = g;
  rtn.b = b;

  return rtn;
}

struct Color ColorLight(struct Color ctx)
{
  struct Color rtn = ctx;

  rtn.r = min(255, rtn.r + HIGHLIGHT);
  rtn.g = min(255, rtn.g + HIGHLIGHT);
  rtn.b = min(255, rtn.b + HIGHLIGHT);

  return rtn;
}

struct Color ColorDark(struct Color ctx)
{
  struct Color rtn = ctx;

  rtn.r = max(0, rtn.r - HIGHLIGHT);
  rtn.g = max(0, rtn.g - HIGHLIGHT);
  rtn.b = max(0, rtn.b - HIGHLIGHT);

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

