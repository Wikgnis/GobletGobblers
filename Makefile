Goblet_Goblers: main.o 
	gcc -o Goblet_Goblers main.o terminal.o input.o board.o
	make clean

main.o : terminal.o input.o board.o
	gcc -c -Wall main.c terminal.o input.o board.o

terminal.o : terminal.c
	gcc -c -Wall terminal.c

input.o : input.c
	gcc -c -Wall input.c

board.o : board.c
	gcc -c board.c

board : board.o
	gcc -o - Wall board board.c
	make clean

clean :
	rm *.o