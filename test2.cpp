//
// Created by 顾天齐 on 2026/7/2.
//
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>
#include <numeric>
#include "test.h"
#include "test2.h"
using namespace std;
bool isValid(int row, int col, char val, vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) { // 判断行里是否重复
        if (board[row][i] == val) {
            return false;
        }
    }
    for (int j = 0; j < 9; j++) { // 判断列里是否重复
        if (board[j][col] == val) {
            return false;
        }
    }
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = startRow; i < startRow + 3; i++) { // 判断9方格里是否重复
        for (int j = startCol; j < startCol + 3; j++) {
            if (board[i][j] == val ) {
                return false;
            }
        }
    }
    return true;
}bool solveSudoku_backtracking(vector<vector<char>>& board) {
    for (int i=0;i<board.size();i++) {
        for (int j=0;j<board.size();j++) {
            if (board[i][j]=='.') {
                for (char c='1';c<='9';c++) {
                    if (isValid(i,j,c,board)) {
                        board[i][j]=c;
                        if (solveSudoku_backtracking(board)) return true;
                        board[i][j]='.';
                    }
                }
                return false;
            }
        }
    }
    return true;
}
void solveSudoku(vector<vector<char>>& board) {
    solveSudoku_backtracking(board);
}
void printSudoku(const vector<vector<char>>& board) {
    // 顶部分隔线
    string line = "+-------+-------+-------+\n";
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0) cout << line; // 每3行打印一次横向分割
        for (int j = 0; j < 9; ++j) {
            if (j % 3 == 0) cout << "| "; // 每3列竖线
            cout << board[i][j] << " ";
        }
        cout << "|\n";
    }
    cout << line; // 底部分隔线
}

/*int main(){
    vector<vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    solveSudoku(board);
    printSudoku(board);


}*/
