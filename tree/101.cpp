#include <iostream>
#include <queue>

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
 * 《对称二叉树》
 * 给你一个二叉树的根节点 root，检查它是否轴对称。
 */
class Solution {
public:
    bool check1(TreeNode* left, TreeNode* right){
        if(left == nullptr && right == nullptr)
            return true;
        if(left == nullptr || right == nullptr)
            return false;
        return (left->val == right->val) && check1(left->left, right->right) && check1(left->right, right->left);
    }
    bool check2(TreeNode* left, TreeNode* right){
        queue<TreeNode*> q;
        q.push(left);
        q.push(right);

        while(q.size()){
            TreeNode* l = q.front(); 
            q.pop();
            TreeNode* r = q.front(); 
            q.pop();

            if(l == nullptr && r == nullptr)
                continue;
            if(l == nullptr || r == nullptr)
                return false;
            if(l->val != r->val)
                return false;

            q.push(l->left);
            q.push(r->right);

            q.push(l->right);
            q.push(r->left);
        }
        return true;
    }
    bool isSymmetric(TreeNode* root) {
        return check2(root, root);
    }
};

int main(){
    Solution s;
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);
    bool res = s.isSymmetric(root);
    cout << (res ? "true" : "false") << endl;
}