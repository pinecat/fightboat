all:		fightboat

fightboat:	fightboat.c fightboat.h
	gcc -lncurses -o fightboat fightboat.c

clean:
	rm -rf *.o fightboat
