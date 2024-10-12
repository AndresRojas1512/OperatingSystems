CC=gcc
CFLAGS=-Wall
app.out: main.o
	$(CC) $(CFLAGS) -o app.out main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o app.out