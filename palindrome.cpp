#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int s_len = s.size();
        int left = 0, right = s_len - 1;
        while(left < right){
            if(!isalpha(s[left]) && !isalnum(s[left])){
                left++;
                continue;
            }
            if(!isalpha(s[right]) && !isalnum(s[right])){
                right--;
                continue;
            }
            if(tolower(s[left]) == tolower(s[right])){
                left++;
                right--;
            }else{
                return false;
                break;
            }
        }   
        return true;
    }
        bool isSubsequence(string s, string t) {
        for(char c : s){
            if(int idx = t.find(c); idx != string::npos){
                t = t.substr(++idx); // 截掉这个之前的。
            }else{
                return false;
            }
        }
        return true;
    }
};

int main (){
    string str = "0P";
    Solution s;
    cout << s.isPalindrome(str) << endl;
    cout << s.isSubsequence("acb", "ahbgdc") << endl;
}