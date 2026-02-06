#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<string> split(const string &s, char delimiter) {
        vector<string> tokens;
        string token;
        for (char c : s) {
            if (c == delimiter) {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
            } else {
                token += c;
            }
        }
        if (!token.empty()) {
            tokens.push_back(token);
        }
        return tokens;
    }
    string simplifyPath(string path) {
        stack<string> st;
        vector<string> files = split(path, '/');
        for(const string &file : files){
            if(file == "" || file == "."){
                continue;
            }else if(file == ".."){
                if(!st.empty())
                    st.pop();
            }else{
                st.push(file);
            }
        }   
        string res = "";
        for(; !st.empty(); st.pop()){
            res = "/" + st.top() + res;
        }
        return res.empty() ? "/" : res;
    }
};

int main(){
    Solution sol;
    string path = "/home//foo/";
    string result = sol.simplifyPath(path);
    cout << result << endl;
    return 0;
}