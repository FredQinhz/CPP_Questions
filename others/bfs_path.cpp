#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct Point {
    int x;
    int y;
    Point (int x_ = -1, int y_ = -1)
    : x(x_), y(y_){}
};
bool isValid(int x, int y, int r, int c){
    if(x < 0 || x >= r || y < 0 || y >= c)
        return false;
    return true;
}
string processXY(int x, int y){
    return ("(" + to_string(x) + "," + to_string(y) + ")");
}

int main() {
    // 分别对应，上 下 左 右
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1}; 

    // 处理输入
    int r, c;
    cin >> r >> c;
    vector<vector<int>> board(r, vector<int>(c));
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            cin >> board[i][j]; 

    unordered_set<string> vis;
    queue<vector<string>> path; // 所有路径的记录
    vector<string> finPath; // 最终路径

    queue<Point> q;
    // 初始化，把起点加入
    q.push({0, 0}); 
    finPath.emplace_back(processXY(0, 0));
    path.emplace(finPath);
    while(!q.empty()){
        Point p = q.front();
        q.pop();
        vector<string> tmpPath = path.front(); // 当前节点路径
        path.pop();

        int px = p.x;
        int py = p.y;

        // 如果是终点，则记录
        if(px == r - 1 && py == c - 1){
            finPath = tmpPath;
            break;
        }
        //如果已访问，则进行下轮循环
        if(vis.find(to_string(px) + to_string(py)) != vis.end()){
            continue;
        }
        

        // 枚举所有情况
        for(int i = 0; i < 4; i++){
            int next_x = px + dx[i];
            int next_y = py + dy[i];
            // 如果能走，并且未访问，则添加至队列
            if(isValid(next_x, next_y, r, c) && board[next_x][next_y] == 0 && vis.find(to_string(next_x) + to_string(next_y)) == vis.end()){
                q.push({next_x, next_y});
                tmpPath.emplace_back(processXY(next_x, next_y)); // 路径扩增。
                path.emplace(tmpPath);
                tmpPath.pop_back(); // 可能还有其他可能，回溯影响
            }
        }
        // 添加已访问
        vis.emplace(to_string(px) + to_string(py));
    }


    for(int i = 0; i < finPath.size(); i++){
        cout << finPath[i] << endl;
    }

    return 0;
}