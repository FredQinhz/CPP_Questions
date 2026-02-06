#include<iostream>
#include<vector>
#include<stack>
#include<climits>

using namespace std;

class MinStack {
public:
    stack<int> st;
    stack<int> minSt;
    MinStack() {
        minSt.push(INT_MAX);
    }
    
    void push(int val) {
        st.push(val);
        if(val <= minSt.top()){
            minSt.push(val);
        }
    }
    
    void pop() {
        if(st.top() == minSt.top()){
            minSt.pop();
        }
        st.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return minSt.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

int main(){
    MinStack* obj = new MinStack();
    obj->push(-2);
    obj->push(0);
    obj->push(-3);
    cout << obj->getMin() << endl;
    obj->pop();
    cout << obj->top() << endl;
    cout << obj->getMin() << endl;
}