#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size() == 0)
            return "";

        //公共前缀比所有字符串都短，随便选一个先
        string prefix = strs[0];
        for (string s : strs) {
            while(!startsWith(prefix, s)){
                if(prefix.size() == 0)
                    return "";
                //公共前缀不匹配就让它变短！
                prefix = prefix.substr(0, prefix.size()-1);
            }
        }
        return prefix;
    }
    bool startsWith(string & str1, string & str2){ // str1 是否为 str2 的前缀
        int n1 = str1.size();
        int n2 = str2.size();
        if(n1 <= n2){
            string tmp = str2.substr(0, n1);
            if(str1 == tmp)
                return true;
            else 
                return false;
        }else{
            return false;
        }
    }
};

int main(){
    Solution s;

    vector<string> strs{ "flower","flow","flight"};
    cout << s.longestCommonPrefix(strs);
}