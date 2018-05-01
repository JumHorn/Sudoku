#ifndef _SUDOKU_H_
#define _SUDOKU_H_

//if the number not sure, filled with 0
struct Grid
{
	int rightnum;
	int possiblenum[9];
	Grid() :rightnum(0)
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
};

#endif