#include<iostream>

using namespace std;

/**
 * 《删除排序列表中的重复元素Ⅱ》
 * 给定一个已排序的链表的头 head ， 删除原始链表中所有重复数字的节点，只留下不同的数字 。返回 已排序的链表 。
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

    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* prev = dummy;
        ListNode* curr = head;

        while (curr != nullptr) {
            bool isDuplicate = (curr->next != nullptr && curr->val == curr->next->val);
            if (isDuplicate) {
                int duplicateVal = curr->val;
                while (curr != nullptr && curr->val == duplicateVal) {
                    ListNode* temp = curr;
                    curr = curr->next;
                    delete temp;
                }
                prev->next = curr;
            } else {
                prev = curr;
                curr = curr->next;
            }
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
    head->next->next->next = new Solution::ListNode(3);
    head->next->next->next->next = new Solution::ListNode(4);
    head->next->next->next->next->next = new Solution::ListNode(4);
    head->next->next->next->next->next->next = new Solution::ListNode(5);
    Solution::ListNode* result = sol.deleteDuplicates(head);
    while(result != NULL){  
        cout << result->val << " ";
        result = result->next;
    }
    cout << endl;
    return 0;
}