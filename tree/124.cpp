#include <iostream>
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
 * 《二叉树中的最大路径和》
    路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。同一个节点在一条路径序列中 至多出现一次 。
    该路径至少包含一个节点，且不一定经过根节点。
    路径和 是路径中各节点值的总和。
    给你一个二叉树的根节点 root ，返回其 最大路径和 。
 */
class Solution {
private:
    int maxSum = INT_MIN;
public:
    int maxPathSum(TreeNode* root){
        maxGain(root);
        return maxSum;
    }

    int maxGain(TreeNode* root) {
        if(!root)
            return 0;

        int leftSum = max(maxGain(root->left), 0); // 小于 0 的需要舍弃，这是为了计算全局答案 maxSum
        int rightSum = max(maxGain(root->right), 0);

        // 更新全局答案 maxSum (两边都加上)
        int newPath = root->val + leftSum + rightSum;
        maxSum = max(maxSum, newPath);

        // 返回：从当前 node 出发，向下走到某个子孙节点的一条“单链路径”的最大和
        return root->val + max(leftSum, rightSum);
    }
};

int main(){
    Solution s;
    TreeNode* root = new TreeNode(-10);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    int res = s.maxPathSum(root);
    cout << res << endl;
    return 0;
}
