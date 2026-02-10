#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> flagMap(m, vector<int>(n, 0));
        int direction = 0;
        int x = 0, y = 0;
        for(int i = 0; i < m * n; i++){
            switch(direction){
                case 0: // 向右
                    if(y < n && !flagMap[x][y] ){
                        flagMap[x][y] = 1;
                        res.emplace_back(matrix[x][y]);
                        y++;
                    }else{
                        y--;
                        direction = 1;
                        x++;
                        i--;
                    }
                    break;
                case 1: // 向下
                    if(x < m && !flagMap[x][y]){
                        flagMap[x][y] = 1;
                        res.emplace_back(matrix[x][y]);
                        x++;                        
                    }else{
                        x--;
                        direction = 2;
                        y--;
                        i--;
                    }
                     break;
                case 2: // 向左
                    if(y >= 0 && !flagMap[x][y]){
                        flagMap[x][y] = 1;
                        res.emplace_back(matrix[x][y]);
                        y--;                        
                    }else{
                        y++;
                        direction = 3;
                        x--;
                        i--;
                    }
                    break;  
                case 3: // 向上
                    if(x >= 0 && !flagMap[x][y]){
                        flagMap[x][y] = 1;
                        res.emplace_back(matrix[x][y]);
                        x--;                        
                    }else{
                        x++;
                        direction = 0;
                        y++;
                        i--;
                    }
                    break;              
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<vector<int>> board = {{1,2,3},{4,5,6},{7,8,9}};
    vector<int> res = s.spiralOrder(board);
    for(int i = 0; i < res.size(); i++){
        cout << i + 1 << ": " << res[i] << endl;
    }
    
}