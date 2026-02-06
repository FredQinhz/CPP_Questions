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
 * 《二叉树的层序遍历》
    给你一个二叉树，请你返回其按层序遍历得到的节点值。
    （即逐层地，从左到右访问所有节点）。
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        vector<vector<int>> result;
        if(!root)
            return result;
        q.push(root);
        
        while(q.size()){
            int len = q.size();
            vector<int> level;
            for(int i = 0; i < len; i++){
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node->val);
                if(node->left)
                    q.push(node->left);
                if(node->right)
                    q.push(node->right);
            }
            result.push_back(level);
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
    vector<vector<int>> res = s.levelOrder(root);
    for(const auto& level : res){
        for(int val : level){
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}
