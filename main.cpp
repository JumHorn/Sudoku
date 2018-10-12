#include<iostream>
#include"sudoku.h"
using namespace std;

int main()
{
	Sudoku s;

	s.setContent("sudoku.txt");
	cout<<s;

	char c='\n';
	int result;
	while(c=='\n')
	{
		result=s.calculate();
		cout<<s;
		if(result==0)
		{
			break;
		}
		cout<<result<<endl;
		c=getchar();
	}

	s.flushContent("result.txt");
}
