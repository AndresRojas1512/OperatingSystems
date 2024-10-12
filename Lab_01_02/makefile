CC=gcc
CFLAGS=-Wall
app.exe: main.o
	$(CC) $(CFLAGS) -o app.exe main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o app.exe