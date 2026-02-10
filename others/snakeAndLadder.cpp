#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    pair<int, int> id2rc(int id, int n){
        int r = (id - 1) / n;
        int c = (id - 1) % n;
        if(r % 2 == 1) // 逆序的r
            c = n - 1 - c;
        return{n - 1 - r, c};
    }   
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        vector<int> vis(n * n + 1, 0); // 1 -> n 范围
        queue<pair<int,int>> q; // pair<id, steps>
        q.emplace(1, 0); 
        while(!q.empty()){
            auto p = q.front();
            q.pop();
            // 枚举所有情况
            for(int i = 1; i <= 6; i++){
                // 得到下一步的格子
                int next_id = p.first + i;
                if(next_id > n * n){ // 超出边界
                    break;
                }
                auto next_rc = id2rc(next_id, n);

                if(int tmp = board[next_rc.first][next_rc.second]; tmp != -1){ // 遇到蛇 梯
                    next_id = tmp;
                    next_rc = id2rc(next_id, n);
                }
                
                // 处理
                if(next_id == n * n){
                    return p.second + 1;
                }
                if(!vis[next_id]){ // 没走过
                    vis[next_id] = p.second + 1;
                    q.emplace(next_id, p.second + 1); 
                }else{ // 走过，比较步数
                    if(vis[next_id] > p.second + 1){
                        vis[next_id] = p.second + 1;
                        q.emplace(next_id, p.second + 1); 
                    }
                } 
            }
        }
        return -1;
    }
};