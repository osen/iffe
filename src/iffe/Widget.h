#include "stent.h"
#include "events.h"

#define Init                                                     \
  static void OnInit(struct InitEvent *);                        \
  static void (*initFunc)(struct InitEvent *) = OnInit;

#define Resize                                                   \
  static void OnResize(struct ResizeEvent *);                    \
  static void (*resizeFunc)(struct ResizeEvent *) = OnResize;

#define Draw                                                     \
  static void OnDraw(struct DrawEvent *);                        \
  static void (*drawFunc)(struct DrawEvent *) = OnDraw;

#define Click                                                    \
  static void OnClick(struct ClickEvent *);                      \
  static void (*clickFunc)(struct ClickEvent *) = OnClick;

#define Destroy                                                  \
  static void OnDestroy(struct DestroyEvent *);                  \
  static void (*destroyFunc)(struct DestroyEvent *) = OnDestroy;

#define widget(T, V)                      \
  struct T;                               \
  typedef ref(T) RefT;                    \
  typedef ref(Widget) RefW;               \
  static void (*initFunc)(struct InitEvent *);       \
  static void (*resizeFunc)(struct ResizeEvent *);   \
  static void (*drawFunc)(struct DrawEvent *);       \
  static void (*clickFunc)(struct ClickEvent *);     \
  static void (*destroyFunc)(struct DestroyEvent *); \
  V                                              \
  static void _OnInit(struct InitEvent *e)       \
  {                                              \
    if(initFunc) initFunc(e);                    \
  }                                              \
  static void _OnResize(struct ResizeEvent *e)   \
  {                                              \
    if(resizeFunc) resizeFunc(e);                \
  }                                              \
  static void _OnDraw(struct DrawEvent *e)       \
  {                                              \
    if(drawFunc) drawFunc(e);                    \
  }                                              \
  static void _OnClick(struct ClickEvent *e)     \
  {                                              \
    if(clickFunc) clickFunc(e);                  \
  }                                              \
  static void _OnDestroy(struct DestroyEvent *e) \
  {                                              \
    if(destroyFunc) destroyFunc(e);              \
  }                                              \
  void _##T##Init(RefW ctx)            \
  {                                    \
    struct EventTable et = { 0 };      \
    et.init = _OnInit;                 \
    et.draw = _OnDraw;                 \
    et.click = _OnClick;               \
    et.destroy = _OnDestroy;           \
    _WidgetSetEventTable(ctx, &et);    \
  }                                    \
  struct T

struct Widget;

void _WidgetSetEventTable(ref(Widget) ctx, struct EventTable *events);

