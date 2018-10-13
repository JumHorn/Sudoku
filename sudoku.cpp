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
bool Sudoku::setContent(const string& content)
{
	ifstream fin(content);
	if (!fin)
	{
		return false;
	}
	char c;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			fin >> c;
			grid[i][j].rightnum = c;
		}
	}

	fullinitzero();

	return true;
}

//the algorithm to calculate the right number
//return the result number,the result number is 
//the number hasn't been comfirmed
int Sudoku::calculate()
{
	int result = 0;

	//for choosing
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (grid[i][j].rightnum == '0')
			{
				result += choosing(i, j);
			}
		}
	}
	return result;
}

//save the result to file
bool Sudoku::flushContent(const string& path)
{
	ofstream fout(path);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			fout << grid[i][j].rightnum << " ";
		}
		fout << endl;
	}
	return true;
}

//when the right number is not zero
//get rid of other possible numbers
void Sudoku::initzero(int row, int column, int number)
{
	for (int i = 0; i < 9; i++)
	{
		grid[row][i].possiblenum[number - 1] = '0';
	}
	for (int i = 0; i < 9; i++)
	{
		grid[i][column].possiblenum[number - 1] = '0';
	}
	for (int i = row / 3 * 3; i < 3 + row / 3 * 3; i++)
	{
		for (int j = column / 3 * 3; j < 3 + column / 3 * 3; j++)
		{
			grid[i][j].possiblenum[number - 1] = '0';
		}
	}
	for(int i=0;i<9;i++)
    {
        grid[row][column].possiblenum[i]='0';
    }
}

//for the first time init zero of all grid
int Sudoku::fullinitzero()
{
	int result = 0;
	//for zero initialization
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (grid[i][j].rightnum == '0')
			{
				result++;
			}
			else
			{
				initzero(i, j, grid[i][j].rightnum-'0');
			}
		}
	}

	return result;
}

//if choosed one,return 0
//otherwize 1 should be returned
int Sudoku::choosing(int row, int column)
{
	//check self
	int index = 0, flag = 0;
	for (int i = 0; i < 9; i++)
	{
		if (grid[row][column].possiblenum[i] != '0')
		{
			index = i;
			flag++;
			if (flag > 1)
			{
				break;
			}
		}
	}
	if (flag == 1)
	{
		//self check
		grid[row][column].rightnum = index + 1+'0';
		initzero(row, column, index + 1);
		return 0;
	}

	//check others
	for (int i = 0; i < 9; i++)
	{
		if (grid[row][column].possiblenum[i] != '0')
		{
			int j;
			for (j = 0; j < 9; j++)
			{
				int k;
				for (k = 0; k < 9; k++)
				{
					if (j != column&&grid[row][j].possiblenum[k] == i + 1+'0')
					{
						break;
					}
				}
				if (k != 9)
				{
					break;
				}
			}
			if (j == 9)
			{
				//row check
				grid[row][column].rightnum = i + 1+'0';
				initzero(row, column, i + 1);
				return 0;
			}
		}
	}

	for (int i = 0; i < 9; i++)
	{
		if (grid[row][column].possiblenum[i] != '0')
		{
			int j;
			for (j = 0; j < 9; j++)
			{
				int k;
				for (k = 0; k < 9; k++)
				{
					if (j != row&&grid[j][column].possiblenum[k] == i + 1+'0')
					{
						break;
					}
				}
				if (k != 9)
				{
					break;
				}
			}
			if (j == 9)
			{
				//column check
				grid[row][column].rightnum = i + 1+'0';
				initzero(row, column, i + 1);
				return 0;
			}
		}
	}

	for (int l = 0; l < 9; l++)
	{
		if (grid[row][column].possiblenum[l] != '0')
		{
			int i;
			for (i = row / 3 * 3; i < 3 + row / 3 * 3; i++)
			{
				int j;
				for (j = column / 3 * 3; j < 3 + column / 3 * 3; j++)
				{
					int k;
					for (k = 0; k < 9; k++)
					{
						if ((i != row || j != column) && grid[i][j].possiblenum[k] == l + 1+'0')
						{
							break;
						}
					}
					if (k != 9)
					{
						break;
					}
				}
				if (j != 3 + column / 3 * 3)
				{
					break;
				}
			}
			if (i == 3 + row / 3 * 3)
			{
				//grid check
				grid[row][column].rightnum = l + 1+'0';
				initzero(row, column, l + 1);
				return 0;
			}
		}
	}

	return 1;
}

//print the result to the screen
ostream& operator<<(ostream& os,Sudoku& s)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			os << s.grid[i][j].rightnum << " ";
		}
		os << endl;
	}
	os << endl;
	return os;
}
