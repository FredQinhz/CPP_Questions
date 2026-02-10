#include <iostream>
#include <vector>

using namespace std;

/**
* 为了原地修改，定义两个状态
* 2: 死->活，旧状态：2%2 = 0 
* 3: 活->死，旧状态：3%2 = 1 
*/
class Solution {
public:
int dx[8] = {-1, -1, -1, 1, 1, 1, 0, 0};
int dy[8] = {-1, 0, 1, -1, 0, 1, -1, 1};
    int getCnt(int x, int y, vector<vector<int>>& board){
        int cnt = 0;
        int tmp_x, tmp_y;
        for(int i = 0; i < 8; i++){
            tmp_x = x + dx[i];
            tmp_y = y + dy[i];
            if(tmp_x >= 0 && tmp_x < board.size() && tmp_y >=0 && tmp_y < board[0].size())
                cnt += board[tmp_x][tmp_y] % 2;
        }
        return cnt;
    }

    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                int live_num = getCnt(i, j, board);
                if(board[i][j] == 1 && (live_num < 2 || live_num > 3) )
                    board[i][j] = 3; // 状态3：活->死
                if(board[i][j] == 0 && live_num == 3)
                    board[i][j] = 2; // 状态2：死->活
            }
        }

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(board[i][j] == 3)
                    board[i][j] = 0;
                else if(board[i][j] == 2)
                    board[i][j] = 1;
            }
        }
        return;
    }

};

int main(){
    Solution s;
    vector<vector<int>> board = {
        {0,1,0},
        {0,0,1},
        {1,1,1},
        {0,0,0}};
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
    s.gameOfLife(board);
    return 0;
}