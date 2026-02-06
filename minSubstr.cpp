#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    unordered_map<char, int> s_map, t_map;

    bool check(){
        for(auto p : t_map){
            if(s_map[p.first] < p.second)
                return false;
        }
        return true;
    }

    string minWindow(string s, string t) {
        int sl = s.size(), tl = t.size();
        string res;
        if(sl < tl)
            return res;
        // 初始化 t_map 哈希表
        for(char c : t)
            t_map[c]++;

        int left = 0, right = - 1; // 滑动窗口边界
        int resL = -1;      // 最终结果左边界
        int len = INT_MAX;  // 最终结果长度
        while(right < sl){
            if(t.find(s[++right]) != string::npos){ // s[right] 当前元素在 t 当中
                s_map[s[right]]++;
            }

            while(check() && left <= right){
                if(int tmp; (tmp = right - left + 1) < len){
                    len = tmp;
                    resL = left;
                }

                if(t.find(s[left]) != string::npos){ // s[left] 当前元素在 t 当中
                    s_map[s[left]]--;
                }
                left++;
            }
        }
        
        if(resL != -1){
            res = s.substr(resL, len);
        }
        return res;
    }
};

int main(){
    Solution solution;
    string s = "ADOBECODEBANC";
    string t = "ABC";
    string str = solution.minWindow(s, t);
}