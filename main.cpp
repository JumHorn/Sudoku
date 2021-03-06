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

#include<iostream>
#include<fstream>
#include"sudoku.h"
using namespace std;

int main()
{
	Sudoku s;
	ifstream fin("sudoku.txt");
	s.setContent(fin);
	s.flushContent(std::cout);

	char c='\n';
	int result=0;
	int preresult=0;
	while(c=='\n')
	{
		preresult=result;
		result=s.calculate();
		cout<<s;
		cout<<result<<endl;
		if(result==preresult||result==0)
		{
			break;
		}
		c=getchar();
	}
	if(result!=0)
	{
		//using assumption
		s.guess();
		cout<<s;
	}
	ofstream fout("result.txt");
	s.flushContent(fout);

	return 0;
}
