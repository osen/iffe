#include "Rect.h"
#include "Size.h"

#include <stdio.h>

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

struct Size RectSize(struct Rect ctx)
{
  return SizeWh(ctx.w, ctx.h);
}

void RectPrint(struct Rect ctx)
{
  printf("Rect: [%i, %i, %i, %i]\n",
    ctx.x, ctx.y, ctx.w, ctx.h);
}

