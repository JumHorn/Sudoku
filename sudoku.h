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

#ifndef _SUDOKU_H_
#define _SUDOKU_H_
#include<string>
using namespace std;

//all the number was 1 bit in the right and possible number
//if the number not sure, filled with 2^9-1 all possible bit are 1
//if the rightnum is 0,it means not sure what exactly it is
class Sudoku
{
public:
	Sudoku();
	~Sudoku();

	int calculate();
	void guess();
	void setContent(istream& is);
	void flushContent(ostream& os);

private:
	int bit[9][9];

	bool guess(int i,int j);
	bool guessCheck(int i,int j,int val);
	void zeroBit(int row,int column,int number);
	int bitCount(int x) const;
	int numberCount();
	int choose(int row,int column);

	friend ostream& operator<<(ostream& os,Sudoku& s);
};

#endif
