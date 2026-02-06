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
 * 给你一个二叉搜索树的根节点 root ，返回 树中任意两不同节点值之间的最小差值 。
 * 差值是一个正数，其数值等于两值之差的绝对值。
 */
class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        vector<int> values;
        inorderTraversal(root, values);
        int minDiff = INT_MAX;
        for (size_t i = 1; i < values.size(); ++i) {
            minDiff = min(minDiff, values[i] - values[i - 1]);
        }
        return minDiff;
    }
    void inorderTraversal(TreeNode* node, vector<int>& vals) { // 中序遍历
        if (!node) 
            return;
        inorderTraversal(node->left, vals);
        vals.push_back(node->val);
        inorderTraversal(node->right, vals);
    }
};

int main(){
    Solution s;
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(2);
    int res = s.getMinimumDifference(root);
    cout << "Minimum Absolute Difference: " << res << endl;
    return 0;
}   