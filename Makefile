all:Solve.out Create.out

Sudoku.o:Sudoku.cpp Sudoku.h
	g++ -c Sudoku.cpp
mainCreate.o:mainCreate.cpp Sudoku.h
	g++ -c mainCreate.cpp
mainSolve.o:mainSolve.cpp Sudoku.h
	g++ -c mainSolve.cpp
Solve.out:Sudoku.o mainSolve.o
	g++ -o Solve.out mainSolve.o Sudoku.o
Create.out:Sudoku.o mainCreate.o
	g++ -o Create.out mainCreate.o Sudoku.o
clean:
	rm *.o
