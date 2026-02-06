#include <iostream>
#include <vector>

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
 * 《二叉搜索树中第K小的元素》
 * 给你一个二叉搜索树的根节点 root ，和一个整数 k ，
 * 请你设计一个算法查找其中第 k 个最小的元素（从 1 开始计数）。
 */
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        return inorderTraversal(root, k);   
    }
    int inorderTraversal(TreeNode* node, int& k) { // 中序遍历
        if (!node) 
            return -1;
        int left = inorderTraversal(node->left, k);
        if(left != -1) 
            return left;

        if(--k == 0) {
            return node->val;
        }

        return inorderTraversal(node->right, k);
    }
};

int main(){
    Solution s;
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);  
    root->right = new TreeNode(4);
    root->left->right = new TreeNode(2);
    int k = 1;
    int res = s.kthSmallest(root, k);
    cout << "The " << k << "th smallest element is: " << res << endl;
    return 0;
}