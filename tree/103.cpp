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
 * 《二叉树的锯齿形层序遍历》
 * 给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。
 * （即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        vector<vector<int>> result;
        if(!root)
            return result;
        
        q.push(root);
        int leftToRight = 1;

        while(q.size()){
            int len = q.size();
            vector<int> level(len);
            for(int i = 0; i < len; i++){
                TreeNode* node = q.front();
                q.pop();
                
                int index = leftToRight ? i : (len - 1 - i);
                level[index] = node->val;
                
                if(node->left)
                    q.push(node->left);
                if(node->right)
                    q.push(node->right);
            }
            result.push_back(level);
            leftToRight = 1 - leftToRight;
        }
        return result;
    }
};

int main(){
    Solution s;
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);  
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    vector<vector<int>> res = s.zigzagLevelOrder(root);
    for(const auto& level : res){
        for(int val : level){
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}