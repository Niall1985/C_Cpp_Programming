#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<int>>&board, int row, int col, int num){
    //check if num exists in row
    for(int x = 0 ; x <= 8 ; x++){
        if(board[row][x] == num){
            return false;
        }
    }

    //check if num exists in col
    for(int x = 0 ; x <= 8 ; x++){
        if(board[x][col] == num){
            return false;
        }
    }

    int startRow = row - (row % 3), startCol = col - (col % 3);
    // check if num exists in 3x3 sub-matrix
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            if(board[i + startRow][j + startCol] == num){
                return false;
            }
        }
    }
    return true;
}

bool solveSudokuRec(vector<vector<int>> &board, int row, int col){
    int n = board.size();
    // base case: Reached nth column of last row
    if(row == n-1 && col == n){
        return true;
    }
    // If last column of the row go to next row
    if(col == n){
        row++;
        col = 0;
    }
    // If cell is already occupied then move forward
    if(board[row][col] != 0){
        return solveSudokuRec(board, row, col+1);
    }
    // If it is safe to place num at current position
    for(int num = 1 ; num <= n ; num++){
        if(isSafe(board, row, col, num)){
            board[row][col] = num;
            if(solveSudokuRec(board, row, col+1)){
                return true;
            }
            board[row][col] = 0;
        }
    }
    return false;
}

void solveSudoku(vector<vector<int>>&board){
    solveSudokuRec(board, 0, 0);
}

int main() {
    vector<vector<int>> board = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0}, 
      	{5, 2, 0, 0, 0, 0, 0, 0, 0}, 
      	{0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0}, 
      	{9, 0, 0, 8, 6, 3, 0, 0, 5}, 
      	{0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0}, 
      	{0, 0, 0, 0, 0, 0, 0, 7, 4}, 
      	{0, 0, 5, 2, 0, 6, 3, 0, 0}};

	solveSudoku(board);
    
  	for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++)
            cout << board[i][j] << " ";
        cout << endl;
    }

    return 0;
}