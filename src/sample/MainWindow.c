#include <iffe/iffe.h>

#include <stdio.h>

widget(MainWindow, Init)
{
  int dummy;
};

void OnInit(struct InitEvent *event)
{
  printf("Hello World\n");
}
