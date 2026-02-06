#include <iostream>
#include <vector>

using namespace std;

/**
 * 《合并两个有序链表》
 * 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
 */
class Solution {
public:
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* current = dummyHead;
        while(list1 != NULL && list2 != NULL){
            if(list1->val < list2->val){
                current->next = list1;
                list1 = list1->next;
            } else {
                current->next = list2;
                list2 = list2->next;
            }
            current = current->next;
        }
        if(list1 != NULL){
            current->next = list1;
        }
        if(list2 != NULL){
            current->next = list2;
        }
        current = dummyHead->next;
        delete dummyHead;
        return current;
    }
};

int main(){
    Solution sol;
    Solution::ListNode* l1 = new Solution::ListNode(2);
    l1->next = new Solution::ListNode(3);
    l1->next->next = new Solution::ListNode(4);

    Solution::ListNode* l2 = new Solution::ListNode(4);
    l2->next = new Solution::ListNode(6);
    l2->next->next = new Solution::ListNode(9);
    Solution::ListNode* result = sol.mergeTwoLists(l1, l2);
    while(result != NULL){
        cout << result->val << " ";
        result = result->next;
    }

    return 0;
}