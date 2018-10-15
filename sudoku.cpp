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
				bit[i][j] = (1<<(c-'1'));
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
			else
			{
				zeroBit(i,j,bit[i][j]);
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
			if(bitCount(bit[i][j])==1)
				fout << bitCount(bit[i][j]-1)+1 << " ";
			else
				fout << 0 << " ";
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
	for (int i = 0; i < 9; i++)
	{
		if((bit[row][column]&(1<<i))==1)
		{
			//check row
			int sum=0;
			for(int j=0;j<9;j++)
			{
				sum+=(bit[j][column]&(1<<i))>>i;
			}
			if(sum==1)
			{
				zeroBit(row,column,bit[row][column]);
				return 0;
			}

			//check column
			sum=0;
			for(int j=0;j<9;j++)
			{
				sum+=(bit[row][j]&(1<<i))>>i;
			}
			if(sum==1)
			{
				zeroBit(row,column,bit[row][column]);
				return 0;
			}

			//check cube
			sum=0;
			for(int j=0;j<9;j++)
			{
				sum+=(bit[row-row%3+j/3][column-column%3+j%3]&(1<<i))>>i;
			}
			if(sum==1)
			{
				zeroBit(row,column,bit[row][column]);
				return 0;
			}
		}
	}
	//init algorithm's next condition
	//
	return 1;
}

//this bit count solution is from java 
//the difference is that java count 32bit integer 
//and we only care about 9 bit integer
int Sudoku::bitCount(int x)
{
	x=x-((x>>1)&0x555);
	x=(x&0x333)+((x>>2)&0x333);
	x=(x+(x>>4))&0xf0f;
	x=x+(x>>8);
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
	if(bitCount(bit[i][j])==1)
		return guess(i,j+1);

	bit[i][j]=0;
	for(int c=0;c<9;c++)
	{
		if(guessCheck(i,j,1<<c))
		{
			bit[i][j]=(1<<c);
			if(guess(i,j+1))
				return true;
			bit[i][j]=0;
		}
	}
	return false;
}

bool Sudoku::guessCheck(int i,int j,int val)
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
			if(s.bitCount(s.bit[i][j])==1)
				os << s.bitCount(s.bit[i][j]-1)+1 << " ";
			else
				os << 0 << " ";
		}
		os << endl;
	}
	os << endl;
	return os;
}
