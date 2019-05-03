connectn.out: connectn.o board.o win.o game.o
	gcc -Wall -g -o connectn.out connectn.o board.o win.o game.o
	
connectn.o: connectn.c board.c win.c game.c connectn.h
	gcc -Wall -g -c connectn.c

board.o: board.c connectn.h
	gcc -Wall -g -c board.c
	
win.o: win.c connectn.h
	gcc -Wall -g -c win.c
	
game.o: game.c connectn.h
	gcc -Wall -g -c game.c
	
clean:
	rm -f connectn.out connectn.o board.o win.o game.o
