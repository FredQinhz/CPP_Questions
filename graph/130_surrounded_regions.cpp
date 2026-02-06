#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**
 * 《被围绕的区域》
 * 给定一个二维的矩阵，包含 'X' 和 'O'（字母 O）。
 * 找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。
 */

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if(board.empty())
            return;

        int rows = board.size();
        int cols = board[0].size();
        // 从边界开始，标记所有与边界相连的 'O'
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(i == 0 || i == rows - 1 || j == 0 || j == cols - 1){
                    if(board[i][j] == 'O'){
                        bfs(board, i, j, rows, cols);
                    }
                }
            }
        }

        // 填充被围绕的 'O'，恢复边界相连的 'O' 
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(board[i][j] == 'O'){
                    board[i][j] = 'X'; // 被围绕的 'O' 填充为 'X'
                } else if(board[i][j] == '#'){
                    board[i][j] = 'O'; // 恢复边界相连的 'O'
                }
            }
        }
    }

private:
    void bfs(vector<vector<char>>& board, int i, int j, int rows, int cols){
        queue<pair<int, int>> q;
        q.push({i, j});
        board[i][j] = '#'; // 标记为边界相连的 'O'

        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while(!q.empty()){
            auto [x, y] = q.front();
            q.pop();
            for(const auto& dir : directions){
                int newX = x + dir.first;
                int newY = y + dir.second;
                if(newX >= 0 && newX < rows && newY >= 0 && newY < cols && board[newX][newY] == 'O'){
                    board[newX][newY] = '#'; // 标记为边界相连的 'O'
                    q.push({newX, newY});
                }
            }
        }
    }
};

int main(){
    Solution sol;
    vector<vector<char>> board = {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}
    };
    sol.solve(board);
    for (const auto& row : board) {
        for (char c : row) {
            cout << c << " ";
        }
        cout << endl;
    }
    return 0;
}