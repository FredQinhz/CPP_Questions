#include <iostream>
#include <cmath>


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
 * 《完全二叉树的节点个数》
    给出一个完全二叉树，求出该树的节点个数。
    说明：
    完全二叉树的定义如下：
    在完全二叉树中，除了最底层节点可能没有左子节点或右子节点外，
    其他每层节点数都达到最大值，并且最底层的节点都集中在该层最左边的若干位置。
    若最底层为第 h 层，则该层包含 1~ 2h 个节点。
 */
class Solution {
public:
    int countNodes(TreeNode* root) {
        if(!root)
            return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
    int countNodes1(TreeNode* root){
        if(!root)
            return 0;

        int l = 0, r = 0;

        TreeNode* left = root->left;
        while(left){
            l++;
            left = left->left;
        }
        TreeNode* right = root->right;
        while(right){
            r++;
            right = right->right;
        }

        if(l == r){
            return pow(2, l+1) - 1;
        }

        return 1 + countNodes1(root->left) + countNodes1(root->right);
    }
};

int main(){
    Solution s;
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    int res = s.countNodes1(root);
    cout << res << endl;
    return 0;
}