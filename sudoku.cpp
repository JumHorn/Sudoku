#include "sudoku.h"
#include<iostream>
#include<fstream>
using namespace std;



Sudoku::Sudoku()
{
}


Sudoku::~Sudoku()
{
}

//read from a file which stores the numbers in it
//9x9 and the unknows correspond to 0
bool Sudoku::init()
{
	ifstream fin("sudoku.txt");
	char c;
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			fin>>c;
			grid[i][j].rightnum = c - '0';
		}
	}
	return true;
}

//the algorithm to calculate the right number
int Sudoku::calculate()
{
	return 0;
}

//save the result to file
bool Sudoku::output()
{
	ofstream fout("result.txt");
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			fout<<grid[i][j].rightnum<<" ";
		}
		fout<<endl;
	}
	return true;
}

//print the result to the screen
void Sudoku::print()
{
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			cout<<grid[i][j].rightnum<<" ";
		}
		cout<<endl;
	}
}
