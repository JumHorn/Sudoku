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
//return the result number,the result number is 
//the number hasn't been comfirmed
int Sudoku::calculate()
{
	int result=0;
	//for zero initialization
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(grid[i][j].rightnum==0)
			{
				result++;
			}
			else
			{
				memset(grid[i][j].possiblenum,0,sizeof(grid[i][j].possiblenum));
				initzero(i,j,grid[i][j].rightnum);
			}
		}
	}

	if(result==0)
	{
		return result;
	}
	result = 0;

	//for choosing
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(grid[i][j].rightnum==0)
			{
				result += choosing(i,j);
			}
		}
	}
	return result;
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
	cout<<endl;
}

//when the right number is not zero
//get rid of other possible numbers
void Sudoku::initzero(int row,int column,int number)
{
	for(int i=0;i<9;i++)
	{
		grid[row][i].possiblenum[number-1] = 0; 
	}
	for(int i=0;i<9;i++)
	{
		grid[i][column].possiblenum[number-1] = 0; 
	}
	for(int i=row/3*3;i<3;i++)
	{
		for(int j=column/3*3;j<3;j++)
		{
			grid[i][j].possiblenum[number-1] = 0;
		}
	}
}

//if choosed one,return 0
//otherwize 1 should be returned
int Sudoku::choosing(int row,int column)
{	
	int hash[9] = {0};
	memset(hash,0,sizeof(hash));
	for(int i=0;i<9;i++)
	{
		if(grid[row][i].rightnum==0)
		{
			for(int j=0;j<9;j++)
			{
				if(grid[row][i].possiblenum[j]!=0)
				{
					hash[grid[row][i].possiblenum[j]]++;
				}
			}
		}
	}
	for(int i=0;i<9;i++)
	{
		if(hash[i]==1)
		{
			grid[row][column].rightnum=i+1;
			initzero(row,column,i+1);
			return 0;
		}
	}
	
	memset(hash,0,sizeof(hash));
	for(int i=0;i<9;i++)
	{
		if(grid[i][column].rightnum==0)
		{
			for(int j=0;j<9;j++)
			{
				if(grid[i][column].possiblenum[j]!=0)
				{
					hash[grid[i][column].possiblenum[j]]++;
				}
			}
		}
	}
	for(int i=0;i<9;i++)
	{
		if(hash[i]==1)
		{
			grid[row][column].rightnum=i+1;
			initzero(row,column,i+1);
			return 0;
		}
	}

	memset(hash,0,sizeof(hash));
	for(int i=row/3*3;i<3;i++)
	{
		for(int j=column/3*3;j<3;j++)
		{
			if(grid[i][j].rightnum==0)
			{
				for(int k=0;k<9;k++)
				{
					if(grid[i][j].possiblenum[k]!=0)
					{
						hash[grid[i][j].possiblenum[k]]++;
					}
				}
			}
		}
	}
	for(int i=0;i<9;i++)
	{
		if(hash[i]==1)
		{
			grid[row][column].rightnum=i+1;
			initzero(row,column,i+1);
			return 0;
		}
	}
	return 1;
}
