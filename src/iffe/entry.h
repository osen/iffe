#define _MainWindowInit                \
  _MainWindowInit(ref(Widget));        \
                                       \
  int _main(int argc, char *argv[]);   \
                                       \
  int main(int argc, char *argv[])     \
  {                                    \
    return _main(argc, argv);          \
  }                                    \
                                       \
  void _MainWindowInit

