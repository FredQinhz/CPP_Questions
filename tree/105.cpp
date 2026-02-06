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
 * 《从前序与中序遍历序列构造二叉树》
 * 给定两个整数数组 preorder 和 inorder ，
 * 其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，
 * 请构造二叉树并返回其根节点。
 */

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty() || inorder.empty())
            return nullptr;

        if(preorder.size() != 0){
            TreeNode* root = new TreeNode(preorder[0]);
            int rootIndex = find(inorder.begin(), inorder.end(), preorder[0]) - inorder.begin();
            
            vector<int> leftInorder(inorder.begin(), inorder.begin() + rootIndex);
            vector<int> rightInorder(inorder.begin() + rootIndex + 1, inorder.end());
            
            vector<int> leftPreorder(preorder.begin() + 1, preorder.begin() + 1 + leftInorder.size());
            vector<int> rightPreorder(preorder.begin() + 1 + leftInorder.size(), preorder.end());
            
            root->left = buildTree(leftPreorder, leftInorder);
            root->right = buildTree(rightPreorder, rightInorder);
            
            return root;
        }
        return nullptr;
    }
};

int main(){
    Solution s;
    vector<int> preorder = {3,9,20,15,7};
    vector<int> inorder = {9,3,15,20,7};
    TreeNode* root = s.buildTree(preorder, inorder);
    return 0;
}