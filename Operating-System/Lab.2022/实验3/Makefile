all: game game-server game-client sync
.PHONY : all

game: game.o game-ipc.o
	gcc game.o game-ipc.o -o game
game-server: game.o game-socket-server.o
	gcc game.o game-socket-server.o -o game-server
game-client: game.o game-socket-client.o
	gcc game.o game-socket-client.o -o game-client
game.o: game.c game.h
	gcc game.c game.h -c
game-ipc.o: game.h game-ipc.c
	gcc game.h game-ipc.c -c
game-socket-server.o: game.h game-socket-server.c
	gcc game.h game-socket-server.c -c
game-socket-client.o: game.h game-socket-client.c
	gcc game.h game-socket-client.c -c

sync: sync.o
	gcc sync.o -lpthread -o sync
sync.o: sync.c
	gcc sync.c -lpthread -c

clean:
	rm *.o *.gch game game-server game-client sync