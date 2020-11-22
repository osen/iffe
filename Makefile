CC=cc
CFLAGS=-Isrc

all:
	$(CC) -osample $(CFLAGS) src/iffe/*.c src/sample/*.c
