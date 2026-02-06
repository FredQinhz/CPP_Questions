#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class UnionFind{
private:
    vector<int> parent;
    vector<int> rank; // 根节点的权重，岛屿的主陆地
public:
    UnionFind(int n){
        rank = vector<int>(n, 0);
        parent = vector<int>(n, 0);
        for(int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int x){
        if(x== parent[x])
            return x;
        else    
            return parent[x] = find(parent[x]);
    }
    void join(int u, int v){
        u = find(u); // 寻找u的根
        v = find(v); // 寻找v的根
        if (u != v) {
            if (rank[u] > rank[v]) {
                parent[v] = u;
            } else if (rank[u] < rank[v]) {
                parent[u] = v;
            } else {
                parent[v] = u;
                rank[u]++;
            }
        }
    }
};
class Solution {
public:

    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int m = grid1.size();
        int n = grid1[0].size();
        int N = m * n;
        UnionFind uf(N);
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid2[i][j]){
                    if(i > 0 && grid2[i - 1][j]){ // 连接上边
                        uf.join(i * n + j, (i-1) * n + j);
                    }
                    if(j > 0 && grid2[i][j - 1]){ // 连接左边
                        uf.join(i * n + j, i * n + j - 1);
                    }
                }
            }
        }

        unordered_set<int> islands;
        for(int i = 0; i < N; i++){
            int r = i / n;
            int c = i % n;
            if(grid2[r][c]){
                islands.emplace(uf.find(i));
            }
        }
        for(int i = 0; i < N; i++){
            int r = i / n;
            int c = i % n;
            if(!grid1[r][c]){ // 如果grid1是海，但是grid2是land，需要删除这片land，因为不是子land
                islands.erase(uf.find(i));
            }
        }
        return islands.size();
    }   
};

int main(){
    Solution s;
    vector<vector<int>> grad1{
        {1,0,1,0,1},
        {1,1,1,1,1},
        {0,0,0,0,0},
        {1,1,1,1,1},
        {1,0,1,0,1}
    };
    vector<vector<int>> grad2{
        {0,0,0,0,0},
        {1,1,1,1,1},
        {0,1,0,1,0},
        {0,1,0,1,0},
        {1,0,0,0,1}
    };
    vector<vector<int>> grad11{
        {1,1,1,1,0,0},
        {1,1,0,1,0,0},
        {1,0,0,1,1,1},
        {1,1,1,0,0,1},
        {1,1,1,1,1,0},
        {1,0,1,0,1,0},
        {0,1,1,1,0,1},
        {1,0,0,0,1,1},
        {1,0,0,0,1,0},
        {1,1,1,1,1,0}
    };
    vector<vector<int>> grad22{
        {1,1,1,1,0,1},
        {0,0,1,0,1,0},
        {1,1,1,1,1,1},
        {0,1,1,1,1,1},
        {1,1,1,0,1,0},
        {0,1,1,1,1,1},
        {1,1,0,1,1,1},
        {1,0,0,1,0,1},
        {1,1,1,1,1,1},
        {1,0,0,1,0,0}
    };    

    int cnt = s.countSubIslands(grad11, grad22);
    cout << cnt;
}