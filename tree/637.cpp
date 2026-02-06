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
 * 《二叉树的层平均值》
 * 给定一个非空二叉树, 返回一个由每层节点平均值组成的数组。
 */
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        queue<TreeNode*> q;
        vector<double> result;
        if(!root)
            return result;
        q.push(root);

        while(q.size()){
            int len = q.size();
            long long sum = 0;
            for(int i = 0; i < len; i++){
                TreeNode* node = q.front();
                q.pop();
                sum += node->val;
                if(node->left)
                    q.push(node->left);
                if(node->right)
                    q.push(node->right);
            }
            result.push_back((double)sum / len);
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
    vector<double> res = s.averageOfLevels(root);
    for(double val : res){
        cout << val << endl;
    }
    return 0;
}