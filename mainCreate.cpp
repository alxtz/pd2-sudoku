#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Sudoku.h"

using namespace std;

int main()
{
	Sudoku ss;
	
	ss.giveQuestion();

	ss.readIn();
	
	int numA,numB;
	cout<<"Plz key in changeNum A"<<endl;
	cin>>numA;
	cout<<"Plz key in changeNum B"<<endl;
        cin>>numB;
	ss.changeNum(numA,numB);
	ss.printSudokuBoard();
	
	cout<<"Plz key in changeRow A(0~2)"<<endl;
        cin>>numA;
        cout<<"Plz key in changeRow B(0~2)"<<endl;
        cin>>numB;
	ss.changeRow(numA,numB);
	ss.printSudokuBoard();

	cout<<"Plz key in changeCol A(0~2)"<<endl;
        cin>>numA;
        cout<<"Plz key in changeCol B(0~2)"<<endl;
        cin>>numB;
        ss.changeCol(numA,numB);
        ss.printSudokuBoard();
	
	cout<<"Plz choose how many timez to rotate"<<endl;
	cin>>numA;
	ss.rotate(numA);
	ss.printSudokuBoard();

	cout<<"Plz choose how to flip(0->垂直 or 1->水平)"<<endl;
	cin>>numA;
	ss.flip(numA);
	ss.printSudokuBoard();
	//ss.solve();
	
	return 0;
}
