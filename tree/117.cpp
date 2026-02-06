#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

/**
 * 《填充每个节点的下一个右侧节点指针 II》
    给定一个二叉树：
        struct Node {
        int val;
        Node *left;
        Node *right;
        Node *next;
        }
    填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL 。
    初始状态下，所有 next 指针都被设置为 NULL 。
 */

class Solution {
public:
    Node* connect1(Node* root) {
        if (!root) 
            return nullptr;  
        
        queue<Node*> q;
        q.push(root);

        while(q.size() > 0){
            int len = q.size();
            Node* prev = nullptr;
            for (int i = 0; i < len; i++) {
                Node* node = q.front();
                q.pop();
                if (prev) {
                    prev->next = node;
                }
                prev = node;

                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            prev->next = nullptr;
        }
        return root;
    }
    Node* connect2(Node* root) {
        if(!root)
            return nullptr;

        Node* head = root; // 当前层的头节点
        Node* dummy = new Node(0); // 下一层的虚拟头节点

        while(head){
            Node* temp = dummy; // 当前处理的下一层头节点
            while(head){
                if(head->left){
                    temp->next = head->left;
                    temp = temp->next;
                }
                if(head->right){
                    temp->next = head->right;
                    temp = temp->next;
                }
                head = head->next;
            }
            head = dummy->next;
            dummy->next = nullptr; // 重置虚拟头节点
        }
        return root;
    }
};

int main(){
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(7);
    Solution s;
    s.connect1(root);
    return 0;
}