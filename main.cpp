#include<iostream>
#include"sudoku.h"
using namespace std;

int main()
{
	Sudoku s;

	s.init("sudoku.txt");
	s.print();
	
	char c='\n';
	int result;
	while(c=='\n')
	{
		result=s.calculate();
		if(result==0)
		{
			s.print();
			break;
		}
		s.print();
		cout<<result<<endl;
		c=getchar();
	}

	s.output();
}
