#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**
 * 《岛屿数量》
 * 给你一个由 '1'（陆地）和 '0'（水）组成的二维网格，请你计算网格中岛屿的数量。
 * 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
 * 你可以假设网格的四个边均被水包围。
 */
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty())
            return 0;

        int rows = grid.size();
        int cols = grid[0].size();
        int islandCount = 0;

        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(grid[i][j] == '1'){
                    islandCount++;
                    dfs(grid, i, j, rows, cols);
                }
            }
        }
        return islandCount;
    }
private:
    void dfs(vector<vector<char>>& grid, int i, int j, int rows, int cols){
        if(i < 0 || i >= rows || j < 0 || j >= cols || grid[i][j] != '1')
            return;

        grid[i][j] = '0'; // 标记为已访问

        dfs(grid, i + 1, j, rows, cols); // 下
        dfs(grid, i - 1, j, rows, cols); // 上
        dfs(grid, i, j + 1, rows, cols); // 右
        dfs(grid, i, j - 1, rows, cols); // 左
    }
    void bfs(vector<vector<char>>& grid, int i, int j, int rows, int cols){
        queue<pair<int, int>> q;
        q.push({i, j});
        grid[i][j] = '0'; // 标记为已访问

        vector<pair<int, int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};

        while(!q.empty()){
            auto [x, y] = q.front();
            q.pop();

            for(const auto& dir : directions){
                int newX = x + dir.first;
                int newY = y + dir.second;

                if(newX >= 0 && newX < rows && newY >= 0 && newY < cols && grid[newX][newY] == '1'){
                    grid[newX][newY] = '0'; // 标记为已访问
                    q.push({newX, newY});
                }
            }
        }
    }
};

int main(){
    Solution s;
    vector<vector<char>> grid = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    int res = s.numIslands(grid);
    cout << "Number of Islands: " << res << endl;
    return 0;
}