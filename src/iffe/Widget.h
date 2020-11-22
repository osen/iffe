#ifndef IFFE_WIDGET_H
#define IFFE_WIDGET_H

#include "stent.h"
#include "events.h"
#include "config.h"

#ifdef USE_X11
  #include <X11/Xlib.h>
#endif

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
  V                                                  \
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
    et.resize = _OnResize;             \
    et.draw = _OnDraw;                 \
    et.click = _OnClick;               \
    et.destroy = _OnDestroy;           \
    _WidgetSetEventTable(ctx, &et);    \
  }                                    \
  static struct T *_ptr;                                  \
  static ref(T) _WidgetCast(ref(Widget) ctx, size_t size, \
    const char* file, int line)                           \
  {                                                       \
    refvoid ud = _WidgetUserData(ctx);                    \
    if(!ud)                                               \
    {                                                     \
      ud = _stent_alloc(size, #T, file, line);            \
      _WidgetSetUserData(ctx, ud);                        \
    }                                                     \
    return cast(T, ud);                                   \
  }                                                       \
  void _##T##Dummy()                                      \
  {                                                       \
    if(_ptr) { };                                         \
    if(_WidgetCast == _WidgetCast) { };                   \
  }                                                       \
  struct T

#define WidgetCast(W)                               \
  _WidgetCast(W, sizeof(*_ptr), __FILE__, __LINE__)

#ifdef STENT_ENABLE
  #define __(T) \
    (WidgetCast(T)[0][0])
#else
  #define __(T) \
    (WidgetCast(T)[0])
#endif

#define WidgetAdd(W, T)                  \
  _widgetLastWidget = _WidgetCreate(W, #T); \
  do                                     \
  {                                      \
    void _##T##Init(ref(Widget) ctx);    \
    ref(Widget) w = _widgetLastWidget;   \
    _widgetLastWidget = NULL;            \
    if(!w) panic("Invalid construct");   \
    _##T##Init(w);                       \
    _WidgetInit(w);                      \
  }                                      \
  while(0)

struct Widget;
struct Application;
struct Size;
struct Rect;

extern ref(Widget)_widgetLastWidget;

ref(Application) WidgetApplication(ref(Widget) ctx);
ref(Widget) WidgetParent(ref(Widget) ctx);
ref(Widget) WidgetWindow(ref(Widget) ctx);
void WidgetDestroy(ref(Widget) ctx);
void WidgetSetSize(ref(Widget) ctx, struct Size size);
struct Size WidgetSize(ref(Widget) ctx);
struct Rect WidgetBounds(ref(Widget) ctx);
void WidgetFlow(ref(Widget) ctx, char *str);

ref(sstream) WidgetType(ref(Widget) ctx);

ref(Widget) _WidgetCreate(ref(Widget) parent, const char *name);
void _WidgetDestroy(ref(Widget) ctx);
int _WidgetDestroyed(ref(Widget) ctx);

void _WidgetSetEventTable(ref(Widget) ctx, struct EventTable *events);
void _WidgetSetUserData(ref(Widget) ctx, refvoid userData);
refvoid _WidgetUserData(ref(Widget) ctx);
void _WidgetSetBounds(ref(Widget) ctx, struct Rect bounds);

void _WidgetInit(ref(Widget) ctx);
void _WidgetResize(ref(Widget) ctx, struct Size size);
void _WidgetDraw(ref(Widget) ctx, struct Rect rect);
void _WidgetClick(ref(Widget) ctx);

#ifdef USE_X11
Window _WidgetWindow(ref(Widget) ctx);
Atom _WidgetDeleteMessage(ref(Widget) ctx);
GC _WidgetGc(ref(Widget) ctx);
#endif

#endif

