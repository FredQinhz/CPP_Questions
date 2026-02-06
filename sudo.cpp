#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool validateLine(int x, int y, vector<vector<char>>& board){
        // 先验证列
        int num = board[x][y] - '0';
        for(int i = 0; i < 9; i++){ // 寻找这一列非己的数字
            if(i != x && board[i][y]  != '.' && ((num ^ (board[i][y] - '0')) == 0))
                return false;
        }

        // 再验证行
        for(int j = 0; j < 9; j++){ // 寻找这一行非己的数字
            if(j != y && board[x][j]  != '.' && ((num ^ (board[x][j] - '0')) == 0))
                return false;
        }
        return true;
    }
    bool validateBox(int x, int y, vector<vector<char>>& board){
        unordered_map<char, int> map;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(char c = board[x + i][y + j]; c != '.')
                    map[c]++;
            }
        }
        for(auto it : map)
            if(it.second > 1)
                return false;
        return true;
    }
    bool isValidSudoku(vector<vector<char>>& board) {
        int flag = true;
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if((i % 3 == 0) && (j % 3 == 0))
                    flag = flag & validateBox(i, j, board);
                if(board[i][j] != '.'){
                    flag = flag & validateLine(i, j, board);
                    if(!flag)
                        return flag;
                }
            }
        }
        return flag;
    }
};

int main(){
    Solution s;
    vector<vector<char>> board = {
        {'9','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}};
    vector<vector<char>> board1 = {
        {'.','.','.','.','5','.','.','1','.'},
        {'.','4','.','3','.','.','.','.','.'},
        {'.','.','.','.','.','3','.','.','1'},
        {'8','.','.','.','.','.','.','2','.'},
        {'.','.','2','.','7','.','.','.','.'},
        {'.','1','5','.','.','.','.','.','.'},
        {'.','.','.','.','.','2','.','.','.'},
        {'.','2','.','9','.','.','.','.','.'},
        {'.','.','4','.','.','.','.','.','.'}};
    bool flag = s.isValidSudoku(board1);
    cout << flag << endl;
    return 0;
}