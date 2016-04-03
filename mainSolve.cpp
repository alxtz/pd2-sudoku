#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Sudoku.h"

using namespace std;

int main()
{
	Sudoku ss;
	cout<<"請輸入你想給的題目"<<endl;
	ss.readIn();	

	ss.solve();

	//printSudokuBoard();
	
	return 0;
}
