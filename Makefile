CC = gcc
CFLAGS = -lpthread

game: main.o building.o ghost.o hunters.o evidence.o room.o
	$(CC) -o game main.o building.o ghost.o hunters.o evidence.o room.o $(CFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

building.o: building.c
	$(CC) -c building.c $(CFLAGS)

ghost.o: ghost.c
	$(CC) -c ghost.c $(CFLAGS)

hunters.o: hunters.c
	$(CC) -c hunters.c $(CFLAGS)
	
evidence.o: evidence.c
	$(CC) -c evidence.c $(CFLAGS)
	
room.o: room.c
	$(CC) -c room.c $(CFLAGS)
	
clean:
	rm -f *.o game
