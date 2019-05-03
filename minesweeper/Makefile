mine_sweeper.out: mine_sweeper.o game.o

mine_sweeper.o: mine_sweeper.c header.h
	gcc -c mine_sweeper.c
	
game.o: game.c header.h
	gcc -c game.c
	
clean: 
	rm -f *.o
	rm -f *.out
