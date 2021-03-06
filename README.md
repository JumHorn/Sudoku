# Introdution
## this program is designed to solve sudoku problems  

I wrote my implementation of this algorithm in C++,though there was definitely room to get it to run quicker in a couple of places.

The theory is very similar to the other solutions, but with a couple of added sections which added a significant amount more code (which is why I'm not just posting my code). To be honest, I think any performance gain you can get from this algorithm is outweighed by the extra complexity of the code.

## The algorithm:

### First 
go through every empty cell and find its possible values (by looking at the square, row and column it's in), store this list of possible values as the cells value   
Whenever a cell's list of possible values gets reduced to a single value, fill in this value and update all the other unfilled cells in the same square, row and column   

### Next 
go through every square, row and column and look for groups of possible values which are the same. If any of these groups have the same size as their amount of possible values, remove them from all other possible value arrays in the square/row/column.   
> e.g. if a row contains three unfilled cells with possible values (1, 2), (1, 2), (1, 3), the third cell can be reduced to (3) and thus filled in. The reason for this is that since the first two cells must collectively hold values 1 & 2, it's impossible for the third to cell to have value 1, so it's only possible value is 3.

### Repeat
Keep repeating this last process until all possible reductions have been made
If the board still isn't filled, we now need to make a guess

### Guess
choose your guess as follows:   
find a group of size two (e.g. if a row has unfilled values (1, 3), (1, 3) then pick one of these cells to guess)   
otherwise find an unfilled cell with the smallest amount of possible values
Once we know our guess, recursively apply the algorithm with all variations of the guess to find a solution.
The two additions to the standard algorithm people are using are:

filtering out groups of identical possibilities
trying to be a bit smarter with our guesses
This algorithm should significantly reduce the number of guesses that need to be made to find a solution, and quite a lot of sudokus can be solved using this without requiring a single guess.

# Usage
the sudoku file format must be like this   

020700000   
397105408   
100093705   
700936000   
830001650   
000500300   
001004896   
900672003   
060019200   

the 0 stand for the unknown number   
run file program in the shell 
the normal way to calculate the result step by step util the result come out

# Technique
1. using bit monipulation to simplify the procedure to find the right number   
as the possible number can be simulated with the position of bit
only need 2^9(short is enough but I still use int) can store all the possible conditions.all the operations can convert to bit count and & and ^ operations
these operations are much faster.

2. add a new method to try to guess the possible number   
try to minimumize the scope of guess with all number solved on rule 1 above   
the most elegant guess solution I have found on leetcode
[link](https://leetcode.com/problems/sudoku-solver/discuss/15853/Simple-and-Clean-Solution-C++)
```C++
class Solution{
private:
    bool check(vector<vector<char> > &board, int i, int j, char val)
    {
        for(int h=0;h<9;h++)
        {
            if(board[i][h]==val) return false; /* check row */
            if(board[h][j]==val) return false; /* check col */
            if(board[i-i%3+h/3][j-j%3+h%3]==val)return false; /* check cube */
        } 
        return true;
    }
    
    bool solveSudoku(vector<vector<char>> &board, int i, int j)
    {
        if(i==9) return true;
        if(j==9) return solveSudoku(board, i+1, 0);  
        if(board[i][j] != '.') return solveSudoku(board, i, j+1);

        for(char c='1'; c<='9'; c++)
        {
            if(check(board, i, j, c))
            {
                board[i][j] = c;
                if(solveSudoku(board, i, j+1)) return true;
                board[i][j] = '.';
            }
        }

        return false;
    }
    
public:
    void solveSudoku(vector<vector<char> >& board) 
    {
        solveSudoku(board, 0, 0);
    }
};
```

# Versions
V1.2
* add bit method to solve this problem quickly
* change the file IO to stream(the std::cout and the fstream are the same)
* implement the next step in the algorithm

V1.1
* add guess to successfully solve variaty of conditions   
and the step next int the above algoritm has not been implemented

V1.0
* an example showing above 
there are some kind of problems can not be solved with only directly find the answer based on the principles