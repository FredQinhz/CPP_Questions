#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows == 1)
            return s;
        int len = s.size();
        int q = len / (2 * numRows - 2);
        int r = len - q * (2 * numRows - 2);
        int map_n = q * (numRows - 1) + (r <= numRows ? 1 : 1 + r - numRows);
        vector<vector<char>> map(numRows, vector<char>(map_n, '#'));

        bool downFlag = true;
        int m = 0, n = 0;
        for(int i = 0; i < len; i++){
            if(downFlag){
                map[m++][n] = s[i];
            }else{
                map[m--][n++] = s[i];
            }

            if(m == numRows){
                m -= 2;
                n++;
                downFlag = false;
            }else if(m == -1){
                m += 2;
                n--;
                downFlag = true;
            }
        }

        string res;
        for(int i = 0; i < numRows; i++){
            for(int j = 0; j < map_n; j++){
                if(map[i][j] != '#')
                    res += map[i][j];
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    string res = s.convert("PAYPALISHIRING", 3);

    string line = "123456";
    int line_l = line.size();
    cout << line_l << endl;
    line.replace(0, line_l, "1234567890");
    cout << line.size() << endl;
