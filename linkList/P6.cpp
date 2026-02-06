#include<iostream>

using namespace std;

/**
 * 《K 个一组翻转链表》
 * 给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。 k 是一个正整数，它的值小于或等于链表的长度。
 * 如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* pre = dummy;
        ListNode* end = dummy;

        while(true){
            for(int i = 0; i < k && end != NULL; i++){
                end = end->next;
            }
            if(end == NULL) 
                break;

            ListNode* next = nullptr;
            ListNode* cur = pre->next;
            for(int i = 0; i < k - 1; i++){
                next = cur->next;
                cur->next = next->next;
                next->next = pre->next;
                pre->next = next;
            }
            pre = cur;
            end = pre;
        }
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

    int k = 2;
    Solution::ListNode* result = sol.reverseKGroup(head, k);
    while(result != NULL){
        cout << result->val << " ";
        result = result->next;
    }

    return 0;
}