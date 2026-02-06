#include<iostream>

using namespace std;

/**
 * 《旋转链表》
 * 给你一个链表的头节点 head ，旋转链表，将链表每个节点向右移动 k 个位置。
 */

class Solution {
public:
    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };
    
    ListNode* rotateRight(ListNode* head, int k) {
        int length = 0;
        ListNode* curr = head;

        while (curr != nullptr) {
            length++;
            curr = curr->next;
        }
        
        if(length == 0) return head;

        k = k % length;
        if(k == 0) return head; 
    
        ListNode* slow = head;
        ListNode* fast = head;
        for (int i = 0; i < k; i++) {
            fast = fast->next;
        }
        while (fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }

        ListNode* newHead = slow->next;
        slow->next = nullptr;
        fast->next = head;

        return newHead;
    }
};

int main(){
    Solution sol;
    Solution::ListNode* head = new Solution::ListNode(1);
    // head->next = new Solution::ListNode(2);
    // head->next->next = new Solution::ListNode(3);
    // head->next->next->next = new Solution::ListNode(4);
    // head->next->next->next->next = new Solution::ListNode(5);
    int k = 1;
    Solution::ListNode* result = sol.rotateRight(head, k);
    while(result != NULL){  
        cout << result->val << " ";
        result = result->next;
    }
    return 0;
}