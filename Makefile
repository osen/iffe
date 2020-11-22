CC=cc
CFLAGS=-Isrc
LDFLAGS=-lX11

all:
	$(CC) -osample $(CFLAGS) src/iffe/*.c src/sample/*.c $(LDFLAGS)
