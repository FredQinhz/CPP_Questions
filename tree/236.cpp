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
 * 《二叉搜索树的最近公共祖先》
    给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
    最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，
    满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr || root == p || root == q){
            return root;
        }

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if(left != nullptr && right != nullptr){
            return root;
        }

        return left != nullptr ? left : right;
    }
    TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 记录两个节点的路径，然后比较路径上的最后一个相同节点
        vector<TreeNode*> pathP, pathQ, path;
        findPath(root, p, pathP, path);
        path.clear();
        findPath(root, q, pathQ, path);
        TreeNode* lca = nullptr;
        for(size_t i = 0; i < pathP.size() && i < pathQ.size(); ++i){
            if(pathP[i] == pathQ[i]){
                lca = pathP[i];
            } else {
                break;
            }
        }
        return lca;
    }
private:
    bool findPath(TreeNode* root, TreeNode* target, vector<TreeNode*>& path, vector<TreeNode*>& temp){
        if(root == nullptr){
            return false;
        }
        temp.push_back(root);

        if(root == target){
            path = temp;
            return true;
        }

        // 若是该节点包含在path内，则返回 true
        if(findPath(root->left, target, path, temp) || findPath(root->right, target, path, temp)){
            return true;
        }
        // 若是不包含，则回溯，剪枝
        temp.pop_back();
        return false;
    }
};

int main(){
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);

    TreeNode* p = root->left;          // 2
    TreeNode* q = root->left->right;   // 4

    Solution solution;
    TreeNode* lca = solution.lowestCommonAncestor(root, p, q);
    if(lca != nullptr){
        cout << "Lowest Common Ancestor: " << lca->val << endl; // Output: 2
    } else {
        cout << "Lowest Common Ancestor not found." << endl;
    }

    return 0;
}