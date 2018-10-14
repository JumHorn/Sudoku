/*
Copyright (c) 2018 JumHorn <JumHorn@gmail.com>.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "sudoku.h"
#include<iostream>
#include<fstream>
using namespace std;

Sudoku::Sudoku()
{
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			bit[i][j]=(1<<9)-1;
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
			if(c!='0')
				bit[i][j] = 1<<(c-'0');
		}
	}

	numberCount();

	return true;
}

//the algorithm to calculate the right number
//return the result number,the result number is 
//the number hasn't been comfirmed
int Sudoku::calculate()
{
	int result = 0;
	//for choose
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (bitCount(bit[i][j]) != 1)
			{
				result += choose(i, j);
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
			fout << bit[i][j] << " ";
		}
		fout << endl;
	}
	return true;
}

//when the right number is not zero
//get rid of other possible numbers
void Sudoku::zeroBit(int row, int column, int number)
{
	for (int i = 0; i < 9; i++)
	{
		bit[row][i] &= ~number;
		bit[i][column] &= ~number;
		bit[row-row%3+i/3][column-column%3+i%3] &= ~number;
	}
}

//count all the unsure number in sudoku
int Sudoku::numberCount()
{
	int result = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (bitCount(bit[i][j]) != 1)
			{
				result++;
			}
			else
			{
				//for zero initialization
				zeroBit(i, j, bit[i][j]);
			}
		}
	}
	return result;
}

//if choosed one,return 0
//otherwize 1 should be returned
int Sudoku::choose(int row, int column)
{
	//check self
	int index = 0, flag = 0;
	for (int i = 0; i < 9; i++)
	{
		if (bit[row][column][i] != '0')
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
		bit[row][column] = index + 1+'0';
		zeroBit(row, column, index + 1);
		return 0;
	}

	//check others
	for (int i = 0; i < 9; i++)
	{
		if (bit[row][column][i] != '0')
		{
			int j;
			for (j = 0; j < 9; j++)
			{
				int k;
				for (k = 0; k < 9; k++)
				{
					if (j != column&&bit[row][j][k] == i + 1+'0')
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
				bit[row][column] = i + 1+'0';
				zeroBit(row, column, i + 1);
				return 0;
			}
		}
	}

	for (int i = 0; i < 9; i++)
	{
		if (bit[row][column][i] != '0')
		{
			int j;
			for (j = 0; j < 9; j++)
			{
				int k;
				for (k = 0; k < 9; k++)
				{
					if (j != row&&bit[j][column][k] == i + 1+'0')
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
				bit[row][column] = i + 1+'0';
				zeroBit(row, column, i + 1);
				return 0;
			}
		}
	}

	for (int l = 0; l < 9; l++)
	{
		if (bit[row][column][l] != '0')
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
						if ((i != row || j != column) && bit[i][j][k] == l + 1+'0')
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
				//bit check
				bit[row][column] = l + 1+'0';
				zeroBit(row, column, l + 1);
				return 0;
			}
		}
	}

	return 1;
}

//this bit count solution is from java 
//the difference is that java count 32bit integer 
//and we only care about 9 bit integer
int Sudoku::bitCount(int x)
{
	x=x-((x>>1)&0x555);
	x=x+((x>>2)&0x333);
	x=x+((x>>4)&0xf0f);
	return x&0xf;
}

//add new method to guess the number
void Sudoku::guess()
{
	guess(0,0);
}

bool Sudoku::guess(int i,int j)
{
	if(i==9)
		return true;
	if(j==9)
		return guess(i+1,0);
	if(bit[i][j]!='0')
		return guess(i,j+1);

	for(char c='1';c<='9';c++)
	{
		if(guessCheck(i,j,c))
		{
			bit[i][j]=c;
			if(guess(i,j+1))
				return true;
			bit[i][j]='0';
		}
	}
	return false;
}

bool Sudoku::guessCheck(int i,int j,char val)
{
	for(int m=0;m<9;m++)
	{
		if(bit[i][m]==val)return false;
		if(bit[m][j]==val)return false;
		if(bit[i-i%3+m/3][j-j%3+m%3]==val)return false;
	}
	return true;
}

//print the result to the screen
ostream& operator<<(ostream& os,Sudoku& s)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			os << s.bit[i][j] << " ";
		}
		os << endl;
	}
	os << endl;
	return os;
}
