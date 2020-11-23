struct Size;

struct Rect
{
  int x;
  int y;
  int w;
  int h;
};

struct Rect RectXywh(int x, int y, int w, int h);
struct Rect RectAdd(struct Rect a, struct Rect b);
struct Size RectSize(struct Rect ctx);
