Sudoku : main.o sudoku.o
	g++ -o Sudoku main.o sudoku.o

sudoku.o : sudoku.cpp sudoku.h
	g++ -c sudoku.cpp

main.o : main.cpp
	g++ -c main.cpp

clean : 
	rm main.o sudoku.o
