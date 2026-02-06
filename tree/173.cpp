#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * 《二叉搜索树迭代器》
    实现一个二叉搜索树迭代器类 BSTIterator ，表示一个按中序遍历二叉搜索树（BST）构造的迭代器：
    BSTIterator(TreeNode* root) 初始化 BSTIterator 类的一个对象。BST 的根节点 root 会作为构造函数的参数传入。
    指向 BST 中最小元素的指针被初始化为一个不存在的数字，意味着调用 next() 将会返回 BST 中的最小元素。
    boolean hasNext() 如果向指针右侧遍历存在数字，则返回 true ；否则返回 false 。
    int next()将指针向右移动，然后返回指针处的数字。
    注意，指针初始化为一个不存在的数字，意味着调用 next() 将会返回 BST 中的最小元素。
 */
class BSTIterator {
private:
    TreeNode* cur;
    stack<TreeNode*> stack;
public:
    BSTIterator(TreeNode* root) {
        cur = root;
    }

    int next() {
        while(cur != nullptr){
            stack.push(cur);
            cur = cur->left;
        }
        cur = stack.top();
        stack.pop();
        int ret = cur->val;
        cur = cur->right;
        return ret;
    }

    bool hasNext() {
        return cur != nullptr || !stack.empty();
    }
};

int main(){
    TreeNode* root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(20);
    BSTIterator* obj = new BSTIterator(root);
    cout << obj->next() << endl;    // return 3
    cout << obj->next() << endl;    // return 7
    cout << obj->hasNext() << endl; // return true
    cout << obj->next() << endl;    // return 9
    cout << obj->hasNext() << endl; // return true
    return 0;
}

