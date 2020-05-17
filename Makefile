OPTIONS=  -std=c99 -g
WARNINGS= -Wall -pedantic -Wextra
OPTIONS+= $(WARNINGS)
OPTIONS+= $(MACROS)
sudoku : sudoku.o
	gcc -o sudoku sudoku.o  $(OPTIONS)

sudoku.o : sudoku.c sudoku.h
	gcc -c sudoku.c $(OPTIONS)


all : sudoku


clean :
	rm *.o -fv *~

cleanall : clean
	rm sudoku -f
