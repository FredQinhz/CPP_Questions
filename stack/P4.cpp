#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<string> st;
        for (const string& token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int b = stoi(st.top()); 
                st.pop();
                int a = stoi(st.top()); 
                st.pop();
                int result;
                if (token == "+") {
                    result = a + b;
                } else if (token == "-") {
                    result = a - b;
                } else if (token == "*") {
                    result = a * b;
                } else { // token == "/"
                    result = a / b;
                }
                st.push(to_string(result));
            } else {
                st.push(token); 
            }
        }
        return stoi(st.top()); // The final result will be the only element left in the stack
    }
};

int main() {
    Solution solution;
    vector<string> tokens = {"2", "1", "+", "3", "*"};
    cout << solution.evalRPN(tokens) << endl; // Output: 9
    return 0;
}