CC=cc
CFLAGS=-Isrc -I/usr/X11R6/include -I/usr/local/include
LDFLAGS=-L/usr/X11R6/lib -L/usr/local/lib -lX11 -lXt -lXaw

all:
	$(CC) -osample $(CFLAGS) src/iffe/*.c src/sample/*.c $(LDFLAGS)
