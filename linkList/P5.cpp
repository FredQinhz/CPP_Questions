#include<iostream>

using namespace std;

/**
 * 《反转链表 II》
 * 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
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

    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if(head == nullptr || left == right) return head;
        
        // int idx = 1;
        // ListNode* cur = head;
        // ListNode* prev = nullptr;

        // while(idx < left){  
        //     prev = cur;
        //     cur = cur->next;
        //     idx++;
        // }

        // ListNode* con = prev;  // 连接反转部分前的节点
        // ListNode* tail = cur;  // 反转部分 反转后的尾节点
        // ListNode* next = nullptr;
        // while(idx <= right){
        //     next = cur->next;
        //     cur->next = prev;
        //     prev = cur;
        //     cur = next;
        //     idx++;
        // }

        // if(con != nullptr){
        //     con->next = prev; // 此时 prev 指向反转部分 反转后的头节点
        // } else {
        //     head = prev;  
        // }
        // tail->next = cur; // 此时 cur 指向原本 right + 1 位置
        // return head;

        // 使用头插法
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* pre = dummy;
        
        for(int i = 1; i < left; i++){
            pre = pre->next;
        }

        ListNode* cur = pre->next;
        ListNode* next = nullptr;
        for(int i = left; i < right; i++){ // 头插法：依次把 cur 的下一个节点插到 pre 之后
            next = cur->next;
            cur->next = next->next;
            next->next = pre->next;
            pre->next = next;
        }

        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};

int main(){
    Solution sol;
    Solution::ListNode* head = new Solution::ListNode(1);
    head->next = new Solution::ListNode(2);
    head->next->next = new Solution::ListNode(3);
    head->next->next->next = new Solution::ListNode(4);
    head->next->next->next->next = new Solution::ListNode(5);

    int left = 2, right = 4;
    Solution::ListNode* result = sol.reverseBetween(head, left, right);
    while(result != NULL){
        cout << result->val << " ";
        result = result->next;
    }

    return 0;
}