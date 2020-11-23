CC=cc
CFLAGS=-Isrc -I/usr/local/include
LDFLAGS=-L/usr/local/lib -lX11

all:
	$(CC) -osample $(CFLAGS) src/iffe/*.c src/sample/*.c $(LDFLAGS)
