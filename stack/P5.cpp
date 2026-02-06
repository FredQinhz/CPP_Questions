#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int calculate(string s) {
        stack<long long> nums;
        stack<char> ops;

        auto precedence = [](char op) {
            if (op == '+' || op == '-') return 1;
            if (op == '*' || op == '/') return 2;
            return 0;
        };

        auto apply = [&](char op) {
            long long b = nums.top(); nums.pop();
            long long a = nums.top(); nums.pop();

            long long result;
            if (op == '+') result = a + b;
            else if (op == '-') result = a - b;
            else if (op == '*') result = a * b;
            else result = a / b;

            nums.push(result);
        };

        int n = s.size();
        bool expectUnary = true;  // 当前位置是否允许一元运算符

        for (int i = 0; i < n; ) {
            if (s[i] == ' ') {
                i++;
                continue;
            }

            // 处理数字
            if (isdigit(s[i])) {
                long long num = 0;
                while (i < n && isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }
                nums.push(num);
                expectUnary = false;
            }
            // 处理左括号
            else if (s[i] == '(') {
                ops.push('(');
                i++;
                expectUnary = true;
            }
            // 处理右括号
            else if (s[i] == ')') { 
                while (!ops.empty() && ops.top() != '(') {
                    apply(ops.top());
                    ops.pop();
                }
                if (!ops.empty() && ops.top() == '(') {
                    ops.pop();
                }
                i++;
                expectUnary = false;
            }
            // 处理运算符
            else {
                char op = s[i];
                // 一元负号处理
                if (op == '-' && expectUnary) {
                    nums.push(0);  // 转为 0 - expr
                }
                while (!ops.empty() && ops.top() != '(' &&
                       precedence(ops.top()) >= precedence(op)) {
                    apply(ops.top());
                    ops.pop();
                }
                ops.push(op);
                i++;
                expectUnary = true;
            }
        }
        // 清空栈
        while (!ops.empty()) {
            apply(ops.top());
            ops.pop();
        }
        return nums.top();
    }
};
int main(){
    Solution solution;
    string expression1 = "(1+(4+5*2)-3)+(6+8)";
    try {
        cout << "Expression 1: " << expression1 << " = " << solution.calculate(expression1) << endl;
    } catch (const exception& e) {
        cout << "Error in expression 1: " << e.what() << endl;
    }
    return 0;
}