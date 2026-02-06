#include <iostream>
#include <vector>

using namespace std;

/**
 * 《两数相加》
 * 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
 * 请你将两个数相加，并以相同形式返回一个表示和的链表。
 * 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 */
class Solution {
public:
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode* dummyHead = new ListNode(0);
        ListNode* current = dummyHead; 
        while(l1 != NULL || l2 != NULL || carry > 0){
            int sum = carry;

            if (l1 != NULL){
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL){
                sum += l2->val;
                l2 = l2->next;
            }

            carry = sum / 10;
            sum %= 10;
            current->next = new ListNode(sum);
            current = current->next;
        }

        current = dummyHead->next;
        delete dummyHead;
        return current;
    }
};

int main(){
    Solution sol;
    Solution::ListNode* l1 = new Solution::ListNode(2);
    l1->next = new Solution::ListNode(4);
    l1->next->next = new Solution::ListNode(3);
    Solution::ListNode* l2 = new Solution::ListNode(5);
    l2->next = new Solution::ListNode(6);
    l2->next->next = new Solution::ListNode(4);
    Solution::ListNode* result = sol.addTwoNumbers(l1, l2);
    while(result != NULL){
        cout << result->val << " ";
        result = result->next;
    }

    return 0;
}