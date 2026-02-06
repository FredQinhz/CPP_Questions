#include<iostream>

using namespace std;

/**
 * 《删除链表的倒数第 n 个结点》
 * 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
 * 
 * tips: 维护两个指针，并以 n + 1 步的延迟更新一个指针。
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

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* first = dummy;
        ListNode* second = dummy;
        for(int i = 0; i <= n; i++){ // 先移动 first 指针 n + 1 步
            first = first->next;
        }
        while(first != NULL){ // 同时移动 first 和 second 指针，即 second 指针最终指向倒数第 n 个节点的前一个节点（因此是 n + 1 步）
            first = first->next;
            second = second->next;
        }

        ListNode* target = second->next;
        second->next = second->next->next;
        delete target;

        ListNode* newHead = dummy->next;
        delete dummy;
        return newHead;
    }
};

int main(){
    Solution sol;
    Solution::ListNode* head = new Solution::ListNode(1);
    head->next = new Solution::ListNode(2);
    head->next->next = new Solution::ListNode(3);
    head->next->next->next = new Solution::ListNode(4);
    head->next->next->next->next = new Solution::ListNode(5);

    int n = 2;
    Solution::ListNode* result = sol.removeNthFromEnd(head, n);
    while(result != NULL){
        cout << result->val << " ";
        result = result->next;
    }
    cout << endl;
    return 0;
}