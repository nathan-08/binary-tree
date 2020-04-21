btree: main.o
	cc -Wall main.o -o bt -lncurses

main.o: main.c
	cc -c main.c
