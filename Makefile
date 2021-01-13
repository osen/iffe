CC=cc
CFLAGS=-Isrc -I/usr/X11R6/include -I/usr/local/include

DLDFLAGS=-L/usr/X11R6/lib -L/usr/local/lib -lX11 -lXt -lXaw

LDFLAGS=-L/usr/X11R6/lib -L/usr/local/lib -static -s \
  -lX11 -lXt -lXaw -lxcb -lICE -lXmu -lXext -lXpm -lXau -lSM -lXdmcp

LLDFLAGS=-L/usr/X11R6/lib -L/usr/local/lib -nostdlib -static -s \
  -lX11 -lXt -lXaw -lxcb -lICE -lXmu -lXext -lXpm -lXau -lSM -lXdmcp -lc

#$(CC) -fPIC -fuse-cxa-atexit -shared -olibxaw.so $(CFLAGS) src/driver/xaw.c $(LLDFLAGS)

all:
	$(CC) -fPIC -shared -olibxaw.so $(CFLAGS) src/driver/xaw.c $(DLDFLAGS)
	$(CC) -osample $(CFLAGS) src/iffe/*.c src/sample/*.c $(DLDFLAGS)
