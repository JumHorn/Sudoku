#include<iostream>
#include"sudoku.h"
using namespace std;

int main()
{
	Sudoku s;

	s.setContent("sudoku.txt");
	cout<<s;

	char c='\n';
	int result=0;
	int preresult=0;
	while(c=='\n')
	{
		preresult=result;
		result=s.calculate();
		cout<<s;
		if(result==preresult||result==0)
		{
			break;
		}
		cout<<result<<endl;
		c=getchar();
	}
	if(result!=0)
	{
		//using assumption
	}
	s.flushContent("result.txt");

	return 0;
}
