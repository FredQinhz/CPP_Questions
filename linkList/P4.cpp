#include <iostream>
#include <unordered_map>

using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

/**
 * 《复制带随机指针的链表》
 * 给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。
 * 构造这个链表的 深拷贝 。深拷贝应该正确复制链表中的每个节点以及它们的随机指针指向的节点（指向链表中的节点或 null）。
 * 返回复制链表的头节点。
 */
class Solution {
public:

    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> nodeMap;
        Node* cur = head;
        while(cur != NULL){
            nodeMap[cur] = new Node(cur->val);
            cur = cur->next;
        }
        cur = head;
        while(cur != NULL){
            nodeMap[cur]->next = nodeMap[cur->next];
            nodeMap[cur]->random = nodeMap[cur->random];
            cur = cur->next;
        }
        return nodeMap[head];
    }
};

int main(){
    Solution sol;
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    node1->next = node2;
    node1->random = node2;  
    node2->random = node2;
    Node* copiedList = sol.copyRandomList(node1);
    Node* cur = copiedList;
    while(cur != NULL){
        cout << "Node value: " << cur->val << ", Random points to: ";
        if(cur->random != NULL){
            cout << cur->random->val << endl;
        } else {
            cout << "NULL" << endl;
        }
        cur = cur->next;
    }
    return 0;
}