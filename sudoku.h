#ifndef _SUDOKU_H_
#define _SUDOKU_H_

//if the number not sure, filled with 0
//if the rightnum is 0,it means not sure what exactly it is
struct Grid
{
	int rightnum;		  //the correct number
	int possiblenum[9];   //the possible number
	Grid() : rightnum(0)
	{
		for (int i = 0; i < 9; i++)
		{
			possiblenum[i] = i + 1;
		}
	}
};

class Sudoku
{
private:
	Grid grid[9][9];
public:
	Sudoku();
	~Sudoku();
	bool init();
	int calculate();
	bool output();
	void print();
};

#endif
