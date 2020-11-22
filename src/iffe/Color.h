#include "config.h"

#ifdef USE_X11
  #include <X11/Xlib.h>
#endif

struct Color
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
};

struct Color ColorRgb(unsigned char r, unsigned char g, unsigned char b);

#ifdef USE_X11
XColor ColorXColor(struct Color ctx);
#endif
