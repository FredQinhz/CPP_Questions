#include <iostream>

using namespace std;

/**
 * 《分隔链表》
 * 给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。
 * 你应当 保留 两个分区中每个节点的初始相对位置。
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
    ListNode* partition(ListNode* head, int x) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* lessTail = dummy;
        ListNode* curr = head;
        ListNode* prev = dummy;

        while(curr != nullptr){
            if(curr->val < x){
                if(lessTail->next == curr){
                    lessTail = lessTail->next;
                    prev = curr;
                    curr = curr->next;
                } else { // curr 节点在 lessTail 之前，需要移动
                    prev->next = curr->next;

                    curr->next = lessTail->next;
                    lessTail->next = curr;
                    lessTail = lessTail->next;

                    curr = prev->next;
                }
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        ListNode* newHead = dummy->next;
        delete dummy;
        return newHead;
    }
    
    ListNode* partitionOld(ListNode* head, int x) {
        ListNode* lessDummy = new ListNode(0);
        ListNode* greaterDummy = new ListNode(0);
        ListNode* lessCurr = lessDummy;
        ListNode* greaterCurr = greaterDummy;
        ListNode* curr = head;

        while (curr != nullptr) {
            if (curr->val < x) {
                lessCurr->next = curr;
                lessCurr = lessCurr->next;
            } else {
                greaterCurr->next = curr;
                greaterCurr = greaterCurr->next;
            }
            curr = curr->next;
        }

        greaterCurr->next = nullptr; // 防止环路
        lessCurr->next = greaterDummy->next;

        ListNode* newHead = lessDummy->next;
        delete lessDummy;
        delete greaterDummy;
        return newHead;
    }
};

int main(){
    Solution sol;
    Solution::ListNode* head = new Solution::ListNode(1);
    head->next = new Solution::ListNode(4);
    head->next->next = new Solution::ListNode(3);
    head->next->next->next = new Solution::ListNode(2);
    head->next->next->next->next = new Solution::ListNode(5);

    int x = 3;
    Solution::ListNode* result = sol.partition(head, x);
    while(result != NULL){  
        cout << result->val << " ";
        result = result->next;
    }
    cout << endl;
    return 0;
}