#include <iostream>
#include <vector>
#include <algorithm>

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
 * 《从中序与后序遍历序列构造二叉树》
 * 给定两个整数数组 inorder 和 postorder ，
 * 其中 inorder 是二叉树的中序遍历， postorder 是同一棵树的后序遍历，
 * 请构造二叉树并返回其根节点。
 */

class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.empty() || postorder.empty())
            return nullptr;

        int rootVal = postorder.back();
        auto it = find(inorder.begin(), inorder.end(), rootVal);
        if (it == inorder.end())
            return nullptr;
        int idx = static_cast<int>(it - inorder.begin());

        vector<int> leftInorder(inorder.begin(), inorder.begin() + idx);
        vector<int> rightInorder(inorder.begin() + idx + 1, inorder.end());

        vector<int> leftPostorder(postorder.begin(), postorder.begin() + idx);
        vector<int> rightPostorder(postorder.begin() + idx, postorder.end() - 1);

        TreeNode* root = new TreeNode(rootVal);
        root->left = buildTree(leftInorder, leftPostorder);
        root->right = buildTree(rightInorder, rightPostorder);

        return root;
    }
};

int main(){
    Solution s;
    vector<int> inorder = {9,3,15,20,7};
    vector<int> postorder = {9,15,7,20,3};
    TreeNode* root = s.buildTree(inorder, postorder);
    return 0;
}